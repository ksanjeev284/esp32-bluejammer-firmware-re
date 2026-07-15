#pragma once
/*
 * ComboChannelSelect Range Pro — hardware-profile + long-range lab config
 *
 * LEGAL: Higher TX power / PA modules increase interference risk.
 * Authorized / shielded lab education only. Prefer REBUILD_SAFE=1 for UI.
 */

// 0 = full dual-nRF24 path | 1 = UI only (no RF TX APIs)
#ifndef REBUILD_SAFE
#define REBUILD_SAFE 0
#endif

// ---------------------------------------------------------------------------
// Hardware profile (matches BOM in hardware/HARDWARE_RANGE.md)
//   0 = STOCK     — basic nRF24L01+ (PCB antenna or short pigtail)
//   1 = PA_LNA    — nRF24L01+ with onboard PA+LNA + SMA (recommended range lab)
//   2 = PA_LNA_HG — PA+LNA + high-gain external antenna assumptions
//                   (longer power settle, lower SPI, optional duty limit)
// ---------------------------------------------------------------------------
#ifndef HW_PROFILE
#define HW_PROFILE 1
#endif

// Boot mode: 1 = BT (like original)
#ifndef INITIAL_STATE
#define INITIAL_STATE 1
#endif

#ifndef INITIAL_CARRIER_CH
#define INITIAL_CARRIER_CH 45
#endif

// ---------------------------------------------------------------------------
// RF PHY — range education knobs
// Data rate: 0=1Mbps  1=2Mbps  2=250kbps
// 250 kbps → best receiver sensitivity on nRF24 (lab link-budget demos)
// ---------------------------------------------------------------------------
#ifndef RF_DATA_RATE_SEL
#if HW_PROFILE >= 1
#define RF_DATA_RATE_SEL 2   // 250kbps for range profile
#else
#define RF_DATA_RATE_SEL 1   // 2Mbps stock (matches original)
#endif
#endif

// PA level: 0=MIN 1=LOW 2=HIGH 3=MAX  (+ LNA enable on PA modules)
#ifndef RF_PA_LEVEL
#define RF_PA_LEVEL 3
#endif
#ifndef RF_PA_LNA_ENABLE
#define RF_PA_LNA_ENABLE 1
#endif

// SPI Hz — PA modules on Dupont wires often need slower SPI
#ifndef RF24_SPI_HZ
#if HW_PROFILE >= 2
#define RF24_SPI_HZ 8000000UL
#elif HW_PROFILE == 1
#define RF24_SPI_HZ 8000000UL
#else
#define RF24_SPI_HZ 10000000UL
#endif
#endif

#ifndef RADIO_BEGIN_RETRIES
#if HW_PROFILE >= 1
#define RADIO_BEGIN_RETRIES 5
#else
#define RADIO_BEGIN_RETRIES 3
#endif
#endif

// Extra ms after SPI begin before radio.begin (PA rails need settle)
#ifndef RADIO_POWER_SETTLE_MS
#if HW_PROFILE >= 2
#define RADIO_POWER_SETTLE_MS 50
#elif HW_PROFILE == 1
#define RADIO_POWER_SETTLE_MS 25
#else
#define RADIO_POWER_SETTLE_MS 5
#endif
#endif

// ---------------------------------------------------------------------------
// Hop / dwell — range vs coverage trade-off
// Longer dwell = more energy per channel (lab “reach” demos);
// shorter dwell = more spectral walk (coverage demos).
// ---------------------------------------------------------------------------
#ifndef HOP_STRATEGY
#define HOP_STRATEGY 1   // 0=ORIGINAL 1=EDU 2=SWEEP
#endif

#ifndef HOP_BATCH
#if HW_PROFILE >= 1
#define HOP_BATCH 24     // fewer SPI writes; longer effective dwell
#else
#define HOP_BATCH 48
#endif
#endif

#ifndef HOP_DELAY_MS
#if HW_PROFILE >= 1
#define HOP_DELAY_MS 3   // slightly longer dwell for PA modules
#else
#define HOP_DELAY_MS 1
#endif
#endif

#ifndef HOP_PRIORITY_PCT
#define HOP_PRIORITY_PCT 70   // more time on protocol centers for range demos
#endif

#ifndef COMPLEMENTARY_DUAL
#define COMPLEMENTARY_DUAL 1
#endif

// Optional TX duty-cycle for PA thermal / lab safety (0=continuous like original)
// When >0: carrier ON for DUTY_ON_MS, soft-idle OFF for DUTY_OFF_MS (educational)
#ifndef RANGE_DUTY_ON_MS
#if HW_PROFILE >= 2
#define RANGE_DUTY_ON_MS 800
#else
#define RANGE_DUTY_ON_MS 0
#endif
#endif
#ifndef RANGE_DUTY_OFF_MS
#if HW_PROFILE >= 2
#define RANGE_DUTY_OFF_MS 200
#else
#define RANGE_DUTY_OFF_MS 0
#endif
#endif

// Extra channel separation between dual PAs to reduce mutual desense
#ifndef DUAL_MIN_SEPARATION
#if HW_PROFILE >= 1
#define DUAL_MIN_SEPARATION 8   // MHz / nRF channel units
#else
#define DUAL_MIN_SEPARATION 1
#endif
#endif

// Lab telemetry
#ifndef EDU_STATS_MS
#define EDU_STATS_MS 2000
#endif
#ifndef EDU_OLED_HUD
#define EDU_OLED_HUD 1
#endif

// Optional: ADC pin for 3.3V rail sense via divider (255 = disabled)
// Wire: 3.3V -- 10k -- ADC -- 10k -- GND  → mid ≈ 1.65V at 3.3V rail
#ifndef VCC_SENSE_PIN
#define VCC_SENSE_PIN 255
#endif
#ifndef VCC_SENSE_R_TOP_KOHM
#define VCC_SENSE_R_TOP_KOHM 10.0f
#endif
#ifndef VCC_SENSE_R_BOT_KOHM
#define VCC_SENSE_R_BOT_KOHM 10.0f
#endif

#ifndef OLED_MIN_FRAME_MS
#define OLED_MIN_FRAME_MS 33
#endif

#ifndef REMEMBER_LAST_MODE
#define REMEMBER_LAST_MODE 1
#endif

#ifndef RADIO_TASK_CORE
#define RADIO_TASK_CORE 0
#endif
#ifndef RADIO_TASK_PRIO
#define RADIO_TASK_PRIO 2
#endif
#ifndef RADIO_TASK_STACK
#define RADIO_TASK_STACK 8192
#endif
