#pragma once
/*
 * IEEE / industry channel maps for nRF24 educational Spectrum Lab
 * ----------------------------------------------------------------
 * nRF24 channel N → frequency = 2400 + N MHz  (N = 0..125)
 *
 * Sources (educational summary — verify against current standards text):
 *  - IEEE 802.11-2020 / 802.11ax / 802.11be: 2.4 GHz 20 MHz channelization
 *    unchanged for Wi-Fi 6/7 in 2.4 GHz (centers every 5 MHz).
 *  - Bluetooth Core Spec: adv 37/38/39 @ 2402 / 2426 / 2480 MHz.
 *  - IEEE 802.15.4-2020 2.4 GHz O-QPSK: channels 11..26,
 *    f = 2405 + 5*(ch-11) MHz.
 *
 * Lab / education only. Not a claim of standard compliance for TX PHY.
 */

#include <stdint.h>

// ---- IEEE 802.11 2.4 GHz (Wi-Fi 4/5/6/7 still use these centers in 2.4) ----
// Center MHz → nRF: 2412→12, 2417→17, ... 2472→72  (ch1..13)
// Non-overlapping US teaching set: 1 / 6 / 11 → 12 / 37 / 62
static const uint8_t IEEE_WIFI_ALL[] = {
    12, 17, 22, 27, 32, 37, 42, 47, 52, 57, 62, 67, 72
};
static const uint8_t IEEE_WIFI_ALL_N = sizeof(IEEE_WIFI_ALL) / sizeof(IEEE_WIFI_ALL[0]);

static const uint8_t IEEE_WIFI_NOLAP[] = { 12, 37, 62 };  // ch 1, 6, 11
static const uint8_t IEEE_WIFI_NOLAP_N = 3;

// Side / overlap educational neighbors (OFDMA density teaching)
static const uint8_t IEEE_WIFI_DENSE[] = {
    12, 14, 16, 37, 39, 41, 62, 64, 66, 72
};
static const uint8_t IEEE_WIFI_DENSE_N = sizeof(IEEE_WIFI_DENSE) / sizeof(IEEE_WIFI_DENSE[0]);

// ---- Bluetooth Classic-style 79×1 MHz (educational AFH sample grid) ----
static const uint8_t IEEE_BT_GRID[] = {
    0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39,
    42, 45, 48, 51, 54, 57, 60, 63, 66, 69, 72, 75, 78
};
static const uint8_t IEEE_BT_GRID_N = sizeof(IEEE_BT_GRID) / sizeof(IEEE_BT_GRID[0]);
static const uint8_t IEEE_BT_FULL_MOD = 79;

// ---- BLE advertising + data samples (Bluetooth Core Spec) ----
// Adv: 2402, 2426, 2480 → nRF 2, 26, 80
static const uint8_t IEEE_BLE_ADV[] = { 2, 26, 80 };
static const uint8_t IEEE_BLE_ADV_N = 3;
static const uint8_t IEEE_BLE_DATA[] = {
    4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 68, 72, 76
};
static const uint8_t IEEE_BLE_DATA_N = sizeof(IEEE_BLE_DATA) / sizeof(IEEE_BLE_DATA[0]);
static const uint8_t IEEE_BLE_FULL_MOD = 81;

// ---- IEEE 802.15.4 / Zigbee / Thread 2.4 GHz (ch 11..26) ----
// f_MHz = 2405 + 5*(ch-11) → nRF = f-2400 = 5 + 5*(ch-11)
static const uint8_t IEEE_154_CH[] = {
    5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80
};  // maps 802.15.4 ch 11..26
static const uint8_t IEEE_154_CH_N = 16;

// Prefer quieter upper channels often used to avoid Wi-Fi 1/6 (teaching set)
static const uint8_t IEEE_154_PREFERRED[] = { 15, 20, 25, 70, 75, 80 };  // 13,14,15,24,25,26
static const uint8_t IEEE_154_PREFERRED_N = 6;

// ---- Wide ISM / hobby RC educational grid ----
static const uint8_t IEEE_RC_GRID[] = {
    0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55,
    60, 65, 70, 75, 80, 85, 90, 95, 100, 105, 110, 115, 120, 125
};
static const uint8_t IEEE_RC_GRID_N = sizeof(IEEE_RC_GRID) / sizeof(IEEE_RC_GRID[0]);
static const uint8_t IEEE_RC_FULL_MOD = 126;

static inline const char* ieeeModeLabel(int mode) {
  switch (mode) {
    case 1: return "BT-classic-edu";
    case 2: return "BLE-CoreSpec-edu";
    case 3: return "IEEE-802.11-2.4";
    case 4: return "ISM-RC-wide";
    case 5: return "IEEE-802.15.4";
    case 6: return "IEEE-coexist-sched";
    default: return "idle";
  }
}
