#pragma once
/*
 * SpectrumLab Next — IEEE-informed next-gen educational firmware config
 *
 * LEGAL: RF continuous-carrier can be unlawful interference.
 * Authorized / shielded lab only. Prefer REBUILD_SAFE=1 for classrooms.
 */

#ifndef REBUILD_SAFE
#define REBUILD_SAFE 0
#endif

// Hardware tier: 0 stock nRF | 1 PA+LNA | 2 PA+LNA high-gain
#ifndef HW_PROFILE
#define HW_PROFILE 1
#endif

// Research engine profile:
//  0 = CLASSIC_COMPAT  (BT/BLE/WiFi/RC only, original-like cycle)
//  1 = IEEE_NEXT       (adds 802.15.4 + coexist scheduler)  ← default
//  2 = RESEARCH_MAX    (denser coexist slices, JSON telemetry always on)
#ifndef LAB_ENGINE
#define LAB_ENGINE 1
#endif

#ifndef INITIAL_STATE
#define INITIAL_STATE 1
#endif
#ifndef INITIAL_CARRIER_CH
#define INITIAL_CARRIER_CH 45
#endif

// PHY
#ifndef RF_DATA_RATE_SEL
#if HW_PROFILE >= 1
#define RF_DATA_RATE_SEL 2
#else
#define RF_DATA_RATE_SEL 1
#endif
#endif
#ifndef RF_PA_LEVEL
#define RF_PA_LEVEL 3
#endif
#ifndef RF_PA_LNA_ENABLE
#define RF_PA_LNA_ENABLE 1
#endif

#ifndef RF24_SPI_HZ
#if HW_PROFILE >= 1
#define RF24_SPI_HZ 8000000UL
#else
#define RF24_SPI_HZ 10000000UL
#endif
#endif

#ifndef RADIO_BEGIN_RETRIES
#define RADIO_BEGIN_RETRIES 5
#endif
#ifndef RADIO_POWER_SETTLE_MS
#if HW_PROFILE >= 2
#define RADIO_POWER_SETTLE_MS 50
#elif HW_PROFILE == 1
#define RADIO_POWER_SETTLE_MS 25
#else
#define RADIO_POWER_SETTLE_MS 5
#endif
#endif

// Hop density
#ifndef HOP_BATCH
#define HOP_BATCH 40
#endif
#ifndef HOP_DELAY_MS
#define HOP_DELAY_MS 1
#endif
#ifndef HOP_PRIORITY_PCT
#define HOP_PRIORITY_PCT 75
#endif
#ifndef COMPLEMENTARY_DUAL
#define COMPLEMENTARY_DUAL 1
#endif
#ifndef DUAL_MIN_SEPARATION
#if HW_PROFILE >= 1
#define DUAL_MIN_SEPARATION 10
#else
#define DUAL_MIN_SEPARATION 2
#endif
#endif

// Wi-Fi teaching: weight non-overlapping 1/6/11 more heavily (IEEE dense BSS lesson)
#ifndef WIFI_NOLAP_WEIGHT_PCT
#define WIFI_NOLAP_WEIGHT_PCT 55
#endif

// Coexist scheduler slice duration (ms) per standard family
#ifndef COEXIST_SLICE_MS
#if LAB_ENGINE >= 2
#define COEXIST_SLICE_MS 40
#else
#define COEXIST_SLICE_MS 80
#endif
#endif

// Optional duty (thermal / average power education)
#ifndef RANGE_DUTY_ON_MS
#if HW_PROFILE >= 2
#define RANGE_DUTY_ON_MS 700
#else
#define RANGE_DUTY_ON_MS 0
#endif
#endif
#ifndef RANGE_DUTY_OFF_MS
#if HW_PROFILE >= 2
#define RANGE_DUTY_OFF_MS 300
#else
#define RANGE_DUTY_OFF_MS 0
#endif
#endif

// Telemetry
#ifndef EDU_STATS_MS
#define EDU_STATS_MS 2000
#endif
#ifndef JSON_TELEMETRY
#if LAB_ENGINE >= 2
#define JSON_TELEMETRY 1
#else
#define JSON_TELEMETRY 1
#endif
#endif
#ifndef EDU_OLED_HUD
#define EDU_OLED_HUD 1
#endif

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
#define RADIO_TASK_STACK 10240
#endif
