#pragma once
/*
 * RangeObserver v0.2 — RPD logger + ESP-NOW marker sync
 */

#ifndef OBS_CHANNEL
#define OBS_CHANNEL 45
#endif

#ifndef RF_DATA_RATE_SEL
#define RF_DATA_RATE_SEL 2
#endif

#ifndef RF24_SPI_HZ
#define RF24_SPI_HZ 8000000UL
#endif

#ifndef RADIO_BEGIN_RETRIES
#define RADIO_BEGIN_RETRIES 5
#endif

#ifndef STATS_MS
#define STATS_MS 500
#endif

#ifndef RPD_SAMPLES
#define RPD_SAMPLES 200
#endif

#ifndef SCAN_ENABLE
#define SCAN_ENABLE 0
#endif
#ifndef SCAN_CH_MIN
#define SCAN_CH_MIN 0
#endif
#ifndef SCAN_CH_MAX
#define SCAN_CH_MAX 80
#endif

#ifndef USE_OLED
#define USE_OLED 1
#endif

// Receive LabUltimate ESP-NOW beacons / markers
#ifndef ENABLE_ESPNOW
#define ENABLE_ESPNOW 1
#endif

// Runtime channel override via serial "ch N"
#ifndef ALLOW_SERIAL_CH
#define ALLOW_SERIAL_CH 1
#endif

#define FW_VERSION "0.5.0-obs5"
