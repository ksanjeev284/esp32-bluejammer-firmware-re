# 08 — References & further reading

Use these as starting points; retrieve full texts via IEEE Xplore, ACM DL, MDPI, PMC, institutional access.

## Standards & primary specs

1. Bluetooth SIG — **Bluetooth Core Specification** (LE physical channels, AFH, CSA, PHYs).  
2. Bluetooth SIG — educational materials on **Adaptive Frequency Hopping**.  
3. IEEE Std **802.11** family (ax/be) — 2.4 GHz coexistence context.  
4. IEEE Std **802.15.4** — neighboring WPAN channelization.  
5. ANSI **C63.27** — wireless coexistence evaluation methods (referenced in medical/LBT studies).

## Scientific / technical papers (BLE focus)

6. V. Poirot, O. Landsiedel — **eAFH: Informed Exploration for Adaptive Frequency Hopping in Bluetooth Low Energy**, DCOSS 2022.  
7. J. Mast et al. — **Enhancing Adaptive Frequency Hopping for Bluetooth Low Energy** (LCN / related proceedings line).  
8. B. Pang et al. — **Bluetooth Low Energy Interference Awareness Scheme…**, *Sensors* 2021 (PMC).  
9. B. Pang et al. — probability-based / improved CSA studies under Wi‑Fi interference (simulation frameworks).  
10. S. Muhammad et al. — **Wireless Coexistence of Cellular LBT Systems and BLE 5**, empirical ANSI-style evaluation (PMC).  
11. M. Siekkinen et al. — **How Low Energy is Bluetooth Low Energy?**, energy efficiency comparison (highly cited).  
12. J. Lee et al. — AFH map prediction / sniffer-related work (Energies / related).  
13. Coexistence studies BLE ↔ IEEE 802.15.4 / 802.11 (various thesis & IEEE papers, 2.4 GHz ISM).  

## Interop / platform-related

14. Research on **nRF24L01+ and BLE advertisement frames** (Disney Research–linked line / similar): cross-radio use of adv channels.  

## Vendor application notes (engineering practice)

15. Nordic Semiconductor — nRF52/nRF24 product specs; BLE SoftDevice / Zephyr docs.  
16. Silicon Labs — BLE AFH measurement / channel map application notes.  
17. Espressif — ESP32 BLE (Bluedroid/NimBLE) programming guides.  

## Simulation / teaching aids

18. MathWorks — Bluetooth–WLAN coexistence examples.  
19. OMNeT++/INET showcases — 802.11 ↔ 802.15.4 coexistence (methods transfer to teaching).  

## How to cite when writing lab reports

```text
Author(s). "Title." Venue, Year. DOI if available.
Accessed: YYYY-MM-DD. URL if open access.
```

## Added in verification pass v2

20. J. Karoliny, T. Blazek, A. Springer, H.-P. Bernhard — **Predicting the Channel Access of Bluetooth Low Energy**, arXiv:2301.08109, 2023. (CSA#1/#2 reconstruction, \(c_{\mathrm{int}}\), passive sniff.)  
21. Nordic Semiconductor — **nRF24L01+ Product Specification** (sensitivity −82/−85/−94 dBm; TX levels 0…−18 dBm).  
22. Idaho National Lab / related technical reports — experimental **Wi‑Fi ↔ BLE** throughput/PER coexistence figures (setup-specific).  
23. NXP AN5185 — Wireless coexistence in 2.4 GHz (802.15.4 / Wi‑Fi / BLE lab methods).  
24. Nordic Developer Academy — BLE advertising PDU structure (AdvA + AdvData).  
25. Bluetooth SIG — BLE 5 extended advertising materials (primary pointer / secondary data).  

## Note on secondary summaries

Wikipedia / blog posts can orient you, but **prefer Core Spec + peer-reviewed measurements** for channel math and coexistence claims.

## How this pack is maintained

Each expansion pass should:

1. Add or amend a numbered doc (`09+`)  
2. Append a row to `12_UPDATE_LOG.md`  
3. Mark claim confidence (High / Medium / Low)  
4. Prefer primary sources over marketing pages
