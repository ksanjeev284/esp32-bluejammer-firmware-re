#pragma once
/*
 * Minimal INA219 driver (no Adafruit dependency) — bus voltage + current
 * Default addr 0x40, 0.1 Ω shunt. Returns false if chip missing.
 */

#include <Wire.h>
#include <math.h>

struct Ina219Sample {
  bool  ok;
  float busV;    // load-side bus voltage
  float shuntV;  // shunt voltage
  float currentA;
  float powerW;
};

class LabIna219 {
 public:
  explicit LabIna219(uint8_t addr = 0x40, float shuntOhms = 0.1f)
      : addr_(addr), shunt_(shuntOhms), ok_(false) {}

  bool begin() {
    // Config: 32V range, gain /8 (320 mV), 12-bit bus/shunt continuous
    // 0x399F is a common Adafruit default-ish continuous mode
    if (!write16(0x00, 0x399F)) {
      ok_ = false;
      return false;
    }
    // Calibration for ~3.2 A max with 0.1 Ω: current_lsb = 3.2/32768 ≈ 0.0001
    // cal = 0.04096 / (current_lsb * Rshunt) = 0.04096 / (0.0001 * 0.1) = 4096
    currentLsb_ = 0.0001f;
    uint16_t cal = (uint16_t)(0.04096f / (currentLsb_ * shunt_));
    if (!write16(0x05, cal)) {
      ok_ = false;
      return false;
    }
    ok_ = true;
    return true;
  }

  bool present() const { return ok_; }

  Ina219Sample read() {
    Ina219Sample s{};
    if (!ok_) return s;
    int16_t shuntRaw = 0, busRaw = 0, curRaw = 0;
    if (!read16(0x01, (uint16_t*)&shuntRaw)) return s;
    if (!read16(0x02, (uint16_t*)&busRaw)) return s;
    if (!read16(0x04, (uint16_t*)&curRaw)) return s;
    s.shuntV = shuntRaw * 0.00001f;          // 10 µV / bit
    s.busV = (busRaw >> 3) * 0.004f;         // 4 mV / bit
    s.currentA = curRaw * currentLsb_;
    s.powerW = s.busV * s.currentA;
    s.ok = true;
    return s;
  }

 private:
  uint8_t addr_;
  float shunt_;
  float currentLsb_ = 0.0001f;
  bool ok_;

  bool write16(uint8_t reg, uint16_t val) {
    Wire.beginTransmission(addr_);
    Wire.write(reg);
    Wire.write((uint8_t)(val >> 8));
    Wire.write((uint8_t)(val & 0xFF));
    return Wire.endTransmission() == 0;
  }
  bool read16(uint8_t reg, uint16_t* out) {
    Wire.beginTransmission(addr_);
    Wire.write(reg);
    if (Wire.endTransmission(false) != 0) return false;
    if (Wire.requestFrom((int)addr_, 2) != 2) return false;
    uint16_t v = ((uint16_t)Wire.read() << 8) | Wire.read();
    *out = v;
    return true;
  }
};
