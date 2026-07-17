#pragma once
/*
 * Onboard CSV logger via LittleFS (no extra SPI — safe with dual nRF24).
 * min_spiffs partition leaves ~128 KB FS — enough for lab walks.
 */

#include <Arduino.h>
#include <LittleFS.h>

class LabFileLog {
 public:
  bool begin() {
    if (!LittleFS.begin(true)) {
      ok_ = false;
      return false;
    }
    ok_ = true;
    File f = LittleFS.open("/labult.csv", "a");
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
    File f = LittleFS.open("/labult.csv", "a");
    if (!f) return;
    f.printf("%lu,%d,%u,%u,%.1f,%u,%.2f,%u,%d,%lu,%.2f,%.3f\n",
             (unsigned long)t, mode, (unsigned)chH, (unsigned)chV, hopRate,
             (unsigned)uniq, vcc, (unsigned)heap, armed, (unsigned long)markers,
             busV, currA);
    f.close();
  }

  // Dump last N bytes to Serial for pull
  void dumpTail(size_t maxBytes = 2048) {
    if (!ok_) {
      Serial.println(F("[LOG] no fs"));
      return;
    }
    File f = LittleFS.open("/labult.csv", "r");
    if (!f) return;
    size_t sz = f.size();
    if (sz > maxBytes) f.seek(sz - maxBytes);
    Serial.println(F("==== labult.csv tail ===="));
    while (f.available()) Serial.write(f.read());
    Serial.println(F("\n==== end ===="));
    f.close();
  }

  void clear() {
    if (!ok_) return;
    LittleFS.remove("/labult.csv");
    File f = LittleFS.open("/labult.csv", "w");
    if (f) {
      f.println(F("t_ms,mode,chH,chV,hop_rate,unique,vcc,heap,armed,markers,busV,currA"));
      f.close();
    }
  }

 private:
  bool ok_ = false;
};
