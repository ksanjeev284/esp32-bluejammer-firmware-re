#pragma once
/*
 * Lab Ultimate TX v0.5
 *
 * v0.1–0.4: FIXED/SLOW, CSA, ESP-NOW, BLE, SoftAP, INA, log, OTA, protect, NVS
 * v0.5: Experiment sequencer, profiles, watchdog, boot reason, ESP-NOW RX cmds,
 *       runtime stats interval, factory reset, host CSA tests
 *
 * LEGAL: Authorized / shielded lab only. Prefer REBUILD_SAFE=1 for classrooms.
 */

#ifndef REBUILD_SAFE
#define REBUILD_SAFE 0
#endif

#ifndef HW_PROFILE
#define HW_PROFILE 1
#endif

#ifndef LAB_ENGINE
#define LAB_ENGINE 1
#endif

#ifndef HOP_STRATEGY
#define HOP_STRATEGY 1
#endif

#ifndef FIXED_CH_H
#define FIXED_CH_H 45
#endif
#ifndef FIXED_CH_V
#define FIXED_CH_V 55
#endif

#ifndef SLOW_DWELL_MS
#define SLOW_DWELL_MS 200
#endif
#ifndef SLOW_SWEEP_MAX_CH
#define SLOW_SWEEP_MAX_CH 125
#endif

#ifndef CSA_DWELL_MS
#define CSA_DWELL_MS 15
#endif
#ifndef CSA_MAP_PRESET
#define CSA_MAP_PRESET 0
#endif
#ifndef CSA1_HOP_INC
#define CSA1_HOP_INC 5
#endif
#ifndef CSA2_CHANNEL_ID
#define CSA2_CHANNEL_ID 0xA5C3
#endif

#ifndef ENABLE_ESPNOW
#define ENABLE_ESPNOW 1
#endif
// Accept commands from RangeObserver (set channel / marker ack)
#ifndef ENABLE_ESPNOW_RX
#define ENABLE_ESPNOW_RX 1
#endif

#ifndef ENABLE_SOFTAP
#define ENABLE_SOFTAP 1
#endif
#ifndef SOFTAP_SSID
#define SOFTAP_SSID "LabUltimate"
#endif
#ifndef SOFTAP_PASS
#define SOFTAP_PASS "labult123"
#endif
#ifndef SOFTAP_CHANNEL
#define SOFTAP_CHANNEL 1
#endif
#ifndef ENABLE_CAPTIVE_PORTAL
#define ENABLE_CAPTIVE_PORTAL 1
#endif
#ifndef ENABLE_WEB_OTA
#define ENABLE_WEB_OTA 1
#endif

#ifndef ENABLE_BLE_SCAN
#define ENABLE_BLE_SCAN 1
#endif
#ifndef BLE_SCAN_TIME_SEC
#define BLE_SCAN_TIME_SEC 3
#endif
#ifndef BLE_SCAN_INTERVAL_MS
#define BLE_SCAN_INTERVAL_MS 8000
#endif

#ifndef ENABLE_INA219
#define ENABLE_INA219 1
#endif
#ifndef INA219_ADDR
#define INA219_ADDR 0x40
#endif
#ifndef INA219_SHUNT_OHMS
#define INA219_SHUNT_OHMS 0.1f
#endif
#ifndef INA219_MAX_EXPECT_A
#define INA219_MAX_EXPECT_A 3.2f
#endif
#ifndef CURRENT_LIMIT_A
#define CURRENT_LIMIT_A 2.5f
#endif
#ifndef CURRENT_LIMIT_ENABLE
#define CURRENT_LIMIT_ENABLE 1
#endif
#ifndef CURRENT_LIMIT_HITS
#define CURRENT_LIMIT_HITS 3
#endif

#ifndef ENABLE_FILE_LOG
#define ENABLE_FILE_LOG 1
#endif
#ifndef FILE_LOG_EVERY_STATS
#define FILE_LOG_EVERY_STATS 1
#endif
#ifndef ENABLE_NVS_SETTINGS
#define ENABLE_NVS_SETTINGS 1
#endif

// Experiment sequencer mode (ST_EXP)
#ifndef ENABLE_EXPERIMENT
#define ENABLE_EXPERIMENT 1
#endif

// Task watchdog (seconds)
#ifndef ENABLE_WATCHDOG
#define ENABLE_WATCHDOG 1
#endif
#ifndef WDT_TIMEOUT_S
#define WDT_TIMEOUT_S 8
#endif

#ifndef REQUIRE_RF_ARM
#define REQUIRE_RF_ARM 1
#endif
#ifndef ARM_PRESS_COUNT
#define ARM_PRESS_COUNT 3
#endif
#ifndef ARM_WINDOW_MS
#define ARM_WINDOW_MS 4000
#endif

#ifndef INITIAL_STATE
#define INITIAL_STATE 1
#endif
#ifndef INITIAL_CARRIER_CH
#define INITIAL_CARRIER_CH 45
#endif

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

// Cap default SPI at 10 MHz (HSPI clone nRF + jumpers fail at 16 MHz on-device).
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

#ifndef HOP_BATCH
#if HOP_STRATEGY == 2 || HOP_STRATEGY == 3
#define HOP_BATCH 1
#else
#define HOP_BATCH 32
#endif
#endif
#ifndef HOP_DELAY_MS
#if HOP_STRATEGY == 2
#define HOP_DELAY_MS SLOW_DWELL_MS
#elif HOP_STRATEGY == 3
#define HOP_DELAY_MS 50
#else
#define HOP_DELAY_MS 1
#endif
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

#ifndef WIFI_NOLAP_WEIGHT_PCT
#define WIFI_NOLAP_WEIGHT_PCT 55
#endif
#ifndef COEXIST_SLICE_MS
#if LAB_ENGINE >= 2
#define COEXIST_SLICE_MS 40
#else
#define COEXIST_SLICE_MS 80
#endif
#endif

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

#ifndef DUTY_RUNTIME_ENABLE
#define DUTY_RUNTIME_ENABLE 1
#endif

#ifndef EDU_STATS_MS
#define EDU_STATS_MS 2000
#endif
#ifndef JSON_TELEMETRY
#define JSON_TELEMETRY 1
#endif
#ifndef CSV_TELEMETRY
#define CSV_TELEMETRY 1
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

#ifndef FW_BANNER
#define FW_BANNER "LabUltimate-TX"
#endif
#ifndef FW_VERSION
#define FW_VERSION "0.5.0-roi5"
#endif
