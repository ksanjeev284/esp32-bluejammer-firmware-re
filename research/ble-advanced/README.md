# BLE Advanced Research Pack (local)

**Status:** Local research workspace only — **not pushed** to GitHub by design.

**Purpose:** Collect **scientific / standards-informed** knowledge about Bluetooth Low Energy (BLE) and turn it into a practical blueprint for a **better educational lab platform** (hardware + firmware + math), improving on the original dual-nRF24 “combo” design *as a teaching and measurement system*.

> **Ethics / law**  
> This pack is for **education, authorized lab coexistence study, and RF engineering learning**.  
> Continuous-carrier RF can cause unlawful interference. Do **not** use these notes to attack networks or devices you do not own.

---

## Documents in this folder

| File | Contents |
| --- | --- |
| [01_BLE_PHY_AND_CHANNELS.md](01_BLE_PHY_AND_CHANNELS.md) | BLE channelization, adv vs data, PHYs, hop logic |
| [02_LITERATURE_SURVEY.md](02_LITERATURE_SURVEY.md) | Journals / papers / standards themes (AFH, coexistence, energy) |
| [03_HARDWARE_ARCHITECTURE.md](03_HARDWARE_ARCHITECTURE.md) | Better hardware stack (MCU, RF, power, sense, observe) |
| [04_FIRMWARE_ARCHITECTURE.md](04_FIRMWARE_ARCHITECTURE.md) | Better firmware logic (modes, AFH-aware maps, dual-core) |
| [05_LINK_BUDGET_AND_CALCULATIONS.md](05_LINK_BUDGET_AND_CALCULATIONS.md) | Formulas, worked numbers, original vs improved |
| [06_BETTER_SYSTEM_DESIGN.md](06_BETTER_SYSTEM_DESIGN.md) | End-to-end “research-grade lab” architecture |
| [07_COMPARISON_ORIGINAL_VS_RESEARCH.md](07_COMPARISON_ORIGINAL_VS_RESEARCH.md) | Gap analysis vs original creator design |
| [08_REFERENCES.md](08_REFERENCES.md) | Citations and links to pursue full PDFs |
| [09_CSA_AFH_VERIFIED.md](09_CSA_AFH_VERIFIED.md) | **CSA#1/#2 math** (period 37 vs ~65536), AFH loop |
| [10_NRF24_DATASHEET_VERIFIED.md](10_NRF24_DATASHEET_VERIFIED.md) | Nordic **−82/−85/−94 dBm**, PA module caveats |
| [11_ADV_PACKETS_AND_TIMING.md](11_ADV_PACKETS_AND_TIMING.md) | Legacy 31 B AdvData, extended ADV, CI timing |
| [12_UPDATE_LOG.md](12_UPDATE_LOG.md) | Changelog of research passes + open questions |
| [calc_worksheets/link_budget_template.csv](calc_worksheets/link_budget_template.csv) | Spreadsheet-ready template |

**Latest verification pass:** see `12_UPDATE_LOG.md` (CSA equations, nRF24 datasheet numbers).

---

## Research question

> How do **peer-reviewed and standards-based** views of BLE (channels, AFH, PHY, coexistence, energy) inform a **hardware + firmware** lab platform that is more accurate, measurable, and robust than a closed dual-nRF24 random-hop design?

---

## One-page conclusion (preview)

1. BLE is **not** “40 random MHz slots.” It is a **structured** 2 MHz grid with **3 fixed advertising centers** and **37 data channels** under **AFH / CSA**.  
2. Academic work stresses **Wi‑Fi overlap**, **channel maps**, **CSA #1 vs #2**, and **coded PHY** robustness — original combo firmware used **`random()%39`**, which is a **poor model** of BLE.  
3. A better platform separates: **(A) stimulus radio**, **(B) observer/sniffer**, **(C) instrumentation**, **(D) safe duty / logging**.  
4. Math shows **hardware EIRP + antenna + power integrity** dominate **distance**; **firmware channel logic** dominates **protocol-relevant effectiveness**.  
5. Best “better version” is a **dual-track kit**: keep dual-nRF24 for controlled ISM experiments **and** add **native BLE (e.g. ESP32 / nRF52)** for true advertising/connection labs.

Start with `01` → `02` → `05` → `06`.
