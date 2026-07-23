/*
 * Dual nRF24 diagnostic for ComboChannelSelect pinout (ESP32 30-pin DevKit)
 * HSPI: CE16 CSN15 SCK14 MOSI13 MISO12
 * VSPI: CE22 CSN21 SCK18 MOSI23 MISO19
 */
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

static const uint8_t CE1 = 16, CSN1 = 15, SCK1 = 14, MISO1 = 12, MOSI1 = 13;
static const uint8_t CE2 = 22, CSN2 = 21, SCK2 = 18, MISO2 = 19, MOSI2 = 23;

SPIClass spiH(HSPI);
SPIClass spiV(VSPI);

static void dumpPins(const char* name, uint8_t ce, uint8_t csn, uint8_t sck, uint8_t miso, uint8_t mosi) {
  Serial.printf("%s pins: CE=%u CSN=%u SCK=%u MISO=%u MOSI=%u\n", name, ce, csn, sck, miso, mosi);
}

static bool tryBus(const char* name, SPIClass& spi, uint8_t ce, uint8_t csn,
                   uint8_t sck, uint8_t miso, uint8_t mosi, uint32_t hz) {
  spi.end();
  delay(5);
  spi.begin(sck, miso, mosi, csn);
  delay(10);

  RF24 radio(ce, csn, hz);
  bool ok = radio.begin(&spi);
  bool connected = ok && radio.isChipConnected();

  Serial.printf("  SPI %lu Hz -> begin=%s  isChipConnected=%s\n",
                (unsigned long)hz,
                ok ? "YES" : "NO",
                connected ? "YES" : "NO");

  if (ok) {
    Serial.printf("     channel=%u  isPVariant=%s\n",
                  radio.getChannel(),
                  radio.isPVariant() ? "yes" : "no");
    radio.powerDown();
  }
  return ok && connected;
}

static void testOne(const char* name, SPIClass& spi, uint8_t ce, uint8_t csn,
                    uint8_t sck, uint8_t miso, uint8_t mosi) {
  Serial.println();
  Serial.println("================================================");
  dumpPins(name, ce, csn, sck, miso, mosi);
  const uint32_t speeds[] = {1000000UL, 4000000UL, 8000000UL, 10000000UL, 16000000UL};
  bool any = false;
  for (uint32_t hz : speeds) {
    if (tryBus(name, spi, ce, csn, sck, miso, mosi, hz)) any = true;
  }
  Serial.printf(">>> %s overall: %s\n", name, any ? "OK (at least one speed)" : "FAIL at all speeds");
}

void setup() {
  Serial.begin(115200);
  delay(800);
  Serial.println();
  Serial.println("=== ESP32 dual nRF24 DIAGNOSTIC ===");
  Serial.println("ComboChannelSelect pinout (not generic CE4/CSN5)");
  Serial.printf("3V3 rail tip: both modules on 3V3 only, solid GND, caps help\n");

  // Only HSPI module first (if user disconnected VSPI, even cleaner)
  testOne("HSPI nRF#1", spiH, CE1, CSN1, SCK1, MISO1, MOSI1);
  testOne("VSPI nRF#2", spiV, CE2, CSN2, SCK2, MISO2, MOSI2);

  Serial.println();
  Serial.println("=== DONE ===");
  Serial.println("If HSPI fails all speeds: module dead, bad contact, wrong nRF pin order, or weak power.");
  Serial.println("If HSPI works only at 1-4 MHz: long wires / clone module — lower RF24_SPI_HZ further.");
  Serial.println("Stock combo firmwares in this repo default to 10 MHz (not original 16 MHz).");
  Serial.println("Swap modules between buses and reset to see if FAIL follows the module.");
}

void loop() {
  delay(5000);
}
