#!/usr/bin/env python3
"""Host unit tests for educational CSA#1 / CSA#2 (mirrors soft_csa.h).

  python scripts/csa_test.py
"""

from __future__ import annotations

import sys


def ble_data_to_nrf(k: int) -> int:
    return 2 + 2 * min(max(k, 0), 36)


def csa1_seq(hop_inc: int = 5, n: int = 40, full_map: bool = True):
    """Return list of nRF channels for CSA#1 with full map (no remap)."""
    prev = 0
    out = []
    for _ in range(n):
        unmapped = (prev + hop_inc) % 37
        prev = unmapped
        out.append(ble_data_to_nrf(unmapped))
    return out


def csa2_perm(x: int) -> int:
    shuf = [14, 11, 8, 12, 6, 2, 3, 15, 10, 9, 1, 7, 4, 13, 5, 0]
    r = 0
    for i in range(16):
        if x & (1 << i):
            r |= 1 << shuf[i]
    return r & 0xFFFF


def csa2_mam(a: int, b: int) -> int:
    return (17 * a + b) & 0xFFFF


def csa2_prn_e(e: int, ch_id: int) -> int:
    x = (e ^ ch_id) & 0xFFFF
    x = csa2_perm(x)
    x = csa2_mam(x, ch_id)
    x = csa2_perm(x)
    return x


def csa2_seq(ch_id: int = 0xA5C3, n: int = 40, used=None):
    """Full map: unmapped = prn % 37 → nRF."""
    out = []
    for e in range(n):
        prn = csa2_prn_e(e, ch_id)
        unmapped = prn % 37
        if used is not None and unmapped not in used:
            idx = (len(used) * prn) >> 16
            if idx >= len(used):
                idx = len(used) - 1
            unmapped = used[idx]
        out.append(ble_data_to_nrf(unmapped))
    return out


def test_csa1_period():
    # With full map, unmapped sequence period is 37 for coprime hopInc
    s = csa1_seq(5, 37 * 2)
    assert s[:37] == s[37:74], "CSA#1 should period-37 on full map"
    # hopInc=5: first unmapped after 0 is 5 → nRF 12
    assert s[0] == ble_data_to_nrf(5)


def test_csa2_deterministic():
    a = csa2_seq(0xA5C3, 20)
    b = csa2_seq(0xA5C3, 20)
    assert a == b
    c = csa2_seq(0x1234, 20)
    assert a != c


def test_csa2_remap():
    used = [0, 1, 2, 3, 4]  # only low channels allowed
    s = csa2_seq(0xA5C3, 50, used=used)
    for nrf in s:
        # nRF = 2+2k → k = (nrf-2)/2
        k = (nrf - 2) // 2
        assert k in used, f"remapped channel {k} not in used map"


def test_nrf_mapping():
    assert ble_data_to_nrf(0) == 2  # 2402
    assert ble_data_to_nrf(36) == 74  # 2474
    # BLE adv 39 is not data — data max 36


def main() -> int:
    tests = [
        test_nrf_mapping,
        test_csa1_period,
        test_csa2_deterministic,
        test_csa2_remap,
    ]
    failed = 0
    for t in tests:
        try:
            t()
            print(f"OK  {t.__name__}")
        except AssertionError as e:
            print(f"FAIL {t.__name__}: {e}")
            failed += 1
    # print sample sequences for lab notebooks
    print("\nCSA1 sample nRF:", csa1_seq(5, 12))
    print("CSA2 sample nRF:", csa2_seq(0xA5C3, 12))
    if failed:
        print(f"\n{failed} failed")
        return 1
    print("\nAll CSA tests passed")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
