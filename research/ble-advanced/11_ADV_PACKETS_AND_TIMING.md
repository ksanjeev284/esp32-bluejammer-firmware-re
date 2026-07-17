# 11 — Advertising packets, extended ADV, timing (verified)

---

## 1. Legacy advertising (all scanners)

| Item | Value |
| --- | --- |
| Primary channels | **37, 38, 39 only** |
| Adv PDU payload | **6…37 bytes** (header separate) |
| AdvA | **6 bytes** address |
| AdvData usable | up to **31 bytes** after address |
| PHY (classic) | LE 1M primarily |

Legacy PDUs: ADV_IND, ADV_DIRECT_IND, ADV_NONCONN_IND, ADV_SCAN_IND, etc.

---

## 2. Extended advertising (BLE 5+)

| Item | Behavior |
| --- | --- |
| Primary (37–39) | Often **ADV_EXT_IND** pointers (little/no user data) |
| Secondary (0–36) | **AUX_*** PDUs carry larger payloads |
| Data size | up to **~250 bytes** class for manufacturer data (stack/config dependent) |
| PHY options | 1M / 2M / Coded on secondary chains |

**Lab platform implication:**  
To teach BLE5 advertising fully, need **native BLE 5 controller**, not nRF24 tones.

---

## 3. Advertising interval (order of magnitude)

| Setting | Typical range |
| --- | --- |
| Adv interval | **20 ms … several seconds** (app/profile dependent) |
| Connectable fast discovery | often **20–100 ms** class |
| Battery beacons | **100 ms … 1 s+** |

Average current scales roughly with:

\[
I_{\mathrm{avg}} \approx I_{\mathrm{sleep}} + \frac{E_{\mathrm{adv event}}}{T_{\mathrm{adv}}}
\]

where \(E_{\mathrm{adv event}}\) includes TX on **three** primary channels (plus prep).

**Contrast original combo hop:** orders of magnitude denser RF activity than real advertising.

---

## 4. Connection events (recap + energy)

Each event at interval \(c_{\mathrm{int}}\):

- Central transmits first  
- Peripheral may respond  
- Peripheral may **skip** events to save energy  

Hop channel changes **per connection event** (not per microsecond).

**Research firmware dwell recommendation for BLE_FAITHFUL profile:**

\[
T_{\mathrm{dwell}} \in [7.5, 50]\ \mathrm{ms}
\]

aligned with common \(c_{\mathrm{int}}\) teaching values (7.5, 15, 30, 50 ms).

---

## 5. nRF24 interop research note

Published work explores **nRF24L01+ communicating via BLE advertisement frames** (adv-channel-centric interop).  

Implications:

- Adv centers are a **shared research surface** between nRF24 and BLE stacks.  
- Packet-level experiments on **2 / 26 / 80** (nRF) are more scientifically grounded than random `%39`.  
- Still require careful regulatory/lab ethics for any TX.

---

## 6. Verification

| Topic | Confidence |
| --- | --- |
| 31-byte legacy AdvData | High (Core Spec / Nordic Academy) |
| Extended ADV architecture | High (SIG BLE5 materials) |
| Exact max extended payload | Medium–high (depends on PDU type / stack) — verify in Core Spec when implementing |
