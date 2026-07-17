# Power + Vcc sense (PA+LNA)

Dual **nRF24L01+ PA+LNA** modules are the #1 reason range “fails” when firmware is fine.

## Power

| Do | Why |
| --- | --- |
| 5 V into **adapter boards** (if designed for 5 V) or dedicated **3.3 V ≥1–2 A** | PA TX current spikes |
| 100 µF + 100 nF on each module VCC | Decouple |
| Short thick GND to ESP32 | Common ground |
| Avoid long thin USB-only power for dual PA | Brownouts → begin FAIL |

## Vcc sense (optional)

Firmware already supports ADC if you set in `config.h`:

```cpp
#define VCC_SENSE_PIN 34   // example input-only GPIO
```

Divider:

```text
3.3V_rail --- 10k --- GPIO34 --- 10k --- GND
```

Then serial stats print `Vcc≈x.xxV` and CSV column fills.

## Pinout (unchanged)

| Function | GPIO |
| --- | ---: |
| nRF1 CE/CSN/SCK/MOSI/MISO | 16/15/14/13/12 |
| nRF2 CE/CSN/SCK/MOSI/MISO | 22/21/18/23/19 |
| OLED SDA/SCL | 4/5 |
| LED / BOOT | 27 / 0 |
