#pragma once
/*
 * Optional SD CSV logger on dedicated SPI bus (not nRF buses).
 * Pins from config.h: SD_CS/SCK/MISO/MOSI
 */

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

class LabSdLog {
 public:
  LabSdLog(uint8_t cs, uint8_t sck, uint8_t miso, uint8_t mosi)
      : cs_(cs), sck_(sck), miso_(miso), mosi_(mosi), ok_(false), spi_(HSPI) {}

  bool begin() {
    // Use FSPI/HSPI second instance carefully — VSPI often free if we pick free pins
    spi_.begin(sck_, miso_, mosi_, cs_);
    if (!SD.begin(cs_, spi_)) {
      ok_ = false;
      return false;
    }
    ok_ = true;
    // open or create
    File f = SD.open("/labult.csv", FILE_APPEND);
    if (!f) {
      ok_ = false;
      return false;
    }
    if (f.size() == 0) {
      f.println(F("t_ms,mode,chH,chV,hop_rate,unique,vcc,heap,armed,markers,busV,currA"));
    }
    f.close();
    return true;
  }

  bool ok() const { return ok_; }

  void logLine(uint32_t t, int mode, uint8_t chH, uint8_t chV, float hopRate,
               uint16_t uniq, float vcc, uint32_t heap, int armed, uint32_t markers,
               float busV, float currA) {
    if (!ok_) return;
    File f = SD.open("/labult.csv", FILE_APPEND);
    if (!f) return;
    f.printf("%lu,%d,%u,%u,%.1f,%u,%.2f,%u,%d,%lu,%.2f,%.3f\n",
             (unsigned long)t, mode, (unsigned)chH, (unsigned)chV, hopRate,
             (unsigned)uniq, vcc, (unsigned)heap, armed, (unsigned long)markers,
             busV, currA);
    f.close();
  }

 private:
  uint8_t cs_, sck_, miso_, mosi_;
  bool ok_;
  SPIClass spi_;
};
