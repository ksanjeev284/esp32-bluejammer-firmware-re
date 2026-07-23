#pragma once
/*
 * ComboChannelSelect Pro — optimized + effectiveness config
 * Same hardware as original BlueJammer combo pinout.
 *
 * LEGAL: RF continuous-carrier on 2.4 GHz can be unlawful interference.
 * Use only in authorized / shielded lab education. Prefer REBUILD_SAFE=1
 * when you only need UI / telemetry simulation.
 */

// 0 = full dual-nRF24 path | 1 = UI only (no RF TX APIs)
#ifndef REBUILD_SAFE
#define REBUILD_SAFE 0
#endif

// Boot into BT (1) like original .data, or Idle (0)
#ifndef INITIAL_STATE
#define INITIAL_STATE 1
#endif

#ifndef INITIAL_CARRIER_CH
#define INITIAL_CARRIER_CH 45
#endif

// SPI: original used 16 MHz. On-device diag: clone HSPI nRF often fails begin() at
// 16 MHz but passes at ≤10 MHz; VSPI may still pass at 16 MHz. Keep ≤10 MHz default.
#ifndef RF24_SPI_HZ
#define RF24_SPI_HZ 10000000UL
#endif

// Radio bring-up retries
#ifndef RADIO_BEGIN_RETRIES
#define RADIO_BEGIN_RETRIES 3
#endif

// ---------------------------------------------------------------------------
// Hop strategy (education + effectiveness)
//   0 = ORIGINAL  — pure random % mod (matches closed binary math)
//   1 = EDU       — protocol-aware maps + dual complementary coverage (default)
//   2 = SWEEP     — deterministic band sweep (lab measurement / SDR demos)
// ---------------------------------------------------------------------------
#ifndef HOP_STRATEGY
#define HOP_STRATEGY 1
#endif

// Hop tuning
// Original: 100 setChannels then delay 1ms (SPI storm)
// Pro stability: 32 / 2ms
// Pro EDU effectiveness: denser dual coverage without 100-write storm
#ifndef HOP_BATCH
#define HOP_BATCH 48
#endif
#ifndef HOP_DELAY_MS
#define HOP_DELAY_MS 1
#endif

// Within EDU strategy: % of hops that hit protocol priority channels (rest = full band fill)
#ifndef HOP_PRIORITY_PCT
#define HOP_PRIORITY_PCT 60
#endif

// Force the two nRF24 modules onto different channels every hop (2× spectral presence)
#ifndef COMPLEMENTARY_DUAL
#define COMPLEMENTARY_DUAL 1
#endif

// Print lab hop / coverage stats on Serial every N ms (0 = off)
#ifndef EDU_STATS_MS
#define EDU_STATS_MS 2000
#endif

// Show live chH/chV on OLED mode screens (education HUD)
#ifndef EDU_OLED_HUD
#define EDU_OLED_HUD 1
#endif

// UI refresh floor (ms) so OLED I2C doesn't starve other work
#ifndef OLED_MIN_FRAME_MS
#define OLED_MIN_FRAME_MS 33
#endif

// Persist last mode across reboot (NVS)
#ifndef REMEMBER_LAST_MODE
#define REMEMBER_LAST_MODE 1
#endif

// Run RadioTask on core 0; Arduino loop stays on core 1
#ifndef RADIO_TASK_CORE
#define RADIO_TASK_CORE 0
#endif
#ifndef RADIO_TASK_PRIO
#define RADIO_TASK_PRIO 2
#endif
#ifndef RADIO_TASK_STACK
#define RADIO_TASK_STACK 8192
#endif
