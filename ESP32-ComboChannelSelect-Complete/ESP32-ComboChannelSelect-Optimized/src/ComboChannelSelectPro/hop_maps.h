#pragma once
/*
 * Educational 2.4 GHz channel maps for nRF24L01+
 * ------------------------------------------------
 * nRF24 channel N  →  frequency 2400 + N MHz  (N = 0..125)
 *
 * These tables teach how real protocols sit on the ISM band, and they
 * drive the EDU hop strategy so demos land on *relevant* spectrum
 * instead of pure random % small-N (which wastes time off-protocol).
 *
 * Reference (approximate centers):
 *   Wi-Fi ch k  →  2407 + 5*k MHz  →  nRF ch ≈ 7 + 5*k
 *   BLE adv 37/38/39 → 2402 / 2426 / 2480 MHz → nRF 2 / 26 / 80
 *   BT classic → 79×1 MHz slots, nRF 0..78
 *
 * Lab / education only. Do not use for unlawful interference.
 */

#include <stdint.h>

// ---- Bluetooth Classic (AFH-style 79×1 MHz) ----
// Full band 0..78. Priority: evenly spaced samples for fast first-pass coverage.
static const uint8_t MAP_BT_PRI[] = {
    0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 68, 72, 76,
    2, 10, 18, 26, 34, 42, 50, 58, 66, 74
};
static const uint8_t MAP_BT_PRI_N = sizeof(MAP_BT_PRI) / sizeof(MAP_BT_PRI[0]);
static const uint8_t MAP_BT_FULL_MOD = 79;  // 0..78

// ---- BLE ----
// Advertising channels (most visible to scanners) + dense data-band samples.
// Adv: 2402, 2426, 2480 MHz → nRF 2, 26, 80
static const uint8_t MAP_BLE_PRI[] = {
    2, 26, 80,                 // advertising
    4, 8, 12, 16, 20, 24,      // low data region samples
    30, 34, 38, 42, 46, 50,    // mid
    54, 58, 62, 66, 70, 74, 78 // upper data
};
static const uint8_t MAP_BLE_PRI_N = sizeof(MAP_BLE_PRI) / sizeof(MAP_BLE_PRI[0]);
static const uint8_t MAP_BLE_FULL_MOD = 81;  // allow up to ch 80 for adv39

// ---- Wi-Fi 2.4 GHz (centers of ch 1..13 on nRF scale) ----
// Original firmware used random%14 → only nRF 0..13 (~2400–2413 MHz),
// which barely touches Wi-Fi ch1. EDU maps hit real centers:
//   ch1=12, 2=17, 3=22, 4=27, 5=32, 6=37, 7=42,
//   8=47, 9=52, 10=57, 11=62, 12=67, 13=72
static const uint8_t MAP_WIFI_PRI[] = {
    12, 17, 22, 27, 32, 37, 42, 47, 52, 57, 62, 67, 72,
    // also common overlap / side-lobe neighbors for lab visibility
    7, 14, 37, 62, 72
};
static const uint8_t MAP_WIFI_PRI_N = sizeof(MAP_WIFI_PRI) / sizeof(MAP_WIFI_PRI[0]);
static const uint8_t MAP_WIFI_FULL_MOD = 83;  // 0..82 covers Wi-Fi span + margin

// ---- RC / hobby ISM-wide (full nRF legal-ish 0..125) ----
// Priority: every 5 MHz grid + popular RC clusters
static const uint8_t MAP_RC_PRI[] = {
    0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55,
    60, 65, 70, 75, 80, 85, 90, 95, 100, 105, 110, 115, 120, 125,
    40, 50, 60, 70  // denser mid-band
};
static const uint8_t MAP_RC_PRI_N = sizeof(MAP_RC_PRI) / sizeof(MAP_RC_PRI[0]);
static const uint8_t MAP_RC_FULL_MOD = 126;  // 0..125

// Strategy names for serial education
static inline const char* hopStrategyName(int s) {
  switch (s) {
    case 0: return "ORIGINAL (random%mod)";
    case 1: return "EDU (protocol maps + dual complement)";
    case 2: return "SWEEP (deterministic band walk)";
    default: return "UNKNOWN";
  }
}
