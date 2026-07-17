# 12 — Research update log

Running log of expansions and verifications. **Local only — not pushed.**

| Date | Pass | What was added / verified |
| --- | --- | --- |
| 2026-07-15 | v1 | Initial pack 01–08: BLE maps, literature survey, HW/FW design, link budget, comparison, refs |
| 2026-07-15 | v2 | **09** CSA#1/#2 equations from Karoliny et al. arXiv:2301.08109; period 37 vs 65536; CI from AA |
| 2026-07-15 | v2 | **10** Nordic nRF24L01+ sensitivity −82/−85/−94 dBm; TX 0…−18 dBm; PA module caveats |
| 2026-07-15 | v2 | **11** Legacy 31-byte AdvData; extended ADV primary/secondary; dwell timing vs real CI |
| 2026-07-15 | v2 | Cross-check: Wi‑Fi ~10 BLE channels; BLE PER rises under Wi‑Fi in lab studies (setup-specific) |
| 2026-07-15 | v2 | Corrected teaching emphasis: 250 kbps **+12 dB** sensitivity is datasheet-true for **packets** |
| 2026-07-15 | v2 | Soft-AFH vendor −71 dBm example flagged as **non-universal** |

---

## Open items to verify next

- [ ] Exact Core Spec wording for minimum used channels in AFH  
- [ ] Full CSA#2 PRNG bit-exact test vectors for host unit tests  
- [ ] Measured \(P_t\) of common PA+LNA modules (SA lab)  
- [ ] Quantitative PER tables from INL / ANSI papers under fixed geometries  
- [ ] ESP32 NimBLE current vs adv interval curves  
- [ ] LE Audio / isochronous channel notes (BLE5.2+) for future curriculum  

---

## Confidence legend

| Level | Meaning |
| --- | --- |
| **High** | Core Spec or Nordic datasheet or multi-source agree |
| **Medium** | Strong papers / vendor notes; implement carefully |
| **Low** | Anecdote / marketing; need measurement |
