# Architecture Notes

## High-level block diagram

```text
┌─────────────────────────────────────────────────────────┐
│                     ESP32 DevKit                         │
│  ┌──────────────┐   ┌─────────────┐   ┌──────────────┐  │
│  │  setup/loop  │   │  radioTask  │   │  FreeRTOS    │  │
│  │  UI / button │──▶│  hop + TX   │   │  scheduler   │  │
│  └──────┬───────┘   └──────┬──────┘   └──────────────┘  │
│         │                  │                             │
│    ┌────┴────┐      ┌──────┴──────┐                      │
│    │ SSD1306 │      │ HSPI nRF24  │  CE16 CSN15 …        │
│    │ I2C 4/5 │      │ VSPI nRF24  │  CE22 CSN21 …        │
│    └─────────┘      └─────────────┘                      │
│    LED GPIO27   BOOT GPIO0   UART0 115200                │
└─────────────────────────────────────────────────────────┘
```

## State machine

```text
          BOOT short press
    ┌──────────────────────────┐
    ▼                          │
┌───────┐   ┌────┐  ┌─────┐  ┌──────┐  ┌────┐
│ Idle0 │──▶│ BT │─▶│ BLE │─▶│ WiFi │─▶│ RC │──┐
└───────┘   └────┘  └─────┘  └──────┘  └────┘  │
    ▲                                          │
    └──────────────────────────────────────────┘

BOOT long press (~500ms): pause RF (carrier off) until release/restore
```

LED blinks N times for states 1–4.

## Data flow (radioTask)

```text
g_state ──▶ max_channels = {79,39,14,125}[state]
                │
                ▼
         ch = random() % max
                │
        ┌───────┴────────┐
        ▼                ▼
   setChannel(H)    setChannel(V)
        │                │
        └───────┬────────┘
                ▼
     constant carrier already on
```

## Memory regions of interest

| Region | Why it matters |
| --- | --- |
| DROM `0x3F40xxxx` | All UI strings, bitmaps, splash |
| IROM `0x400D2xxx` | Application logic cluster |
| IROM `0x400D00xx` | Literal pool (string ptrs, immediates) |
| BSS `0x3FFC3Bxx` | Runtime radio objects |

## Separation: app vs library

| App (study this) | Library (ignore for behavior) |
| --- | --- |
| setup/loop/radioTask | lwIP, mbedTLS |
| enterState_* | Wi‑Fi / BT controller |
| drawModeBitmap | FreeRTOS internals |
| RF24 wrappers with pins | NVS, OTA stubs |
