#pragma once
/*
 * Soft CSA / AFH educational hop (Lab Ultimate)
 * ---------------------------------------------
 * Reconstructs Bluetooth LE channel selection concepts for nRF24 labs:
 *  - CSA #1: linear hop + remap when outside channel map
 *  - CSA #2: simplified PRNG unmapped + remap (teaching form of Core Spec CSA#2)
 *
 * BLE data channels 0..36 → MHz 2402+2*k → nRF24 channel = 2+2*k
 * Advertising 37/38/39 → nRF 2/26/80 (handled separately in BLE map mode)
 *
 * NOT a full BLE stack. NOT for attacking third-party connections.
 * See BLE-Advanced-Research/09_CSA_AFH_VERIFIED.md
 */

#include <stdint.h>
#include <string.h>

// Default educational channel map: all 37 data channels used
// Bit i set => BLE data channel i is allowed
#ifndef CSA_DEFAULT_MAP_LO
// bits 0..31 of channels 0..31
#define CSA_DEFAULT_MAP_LO 0xFFFFFFFFu
#endif
#ifndef CSA_DEFAULT_MAP_HI
// bits 0..4 of channels 32..36
#define CSA_DEFAULT_MAP_HI 0x1Fu
#endif

// Example "Wi-Fi 1/6/11 crowded" map: clear lower mid channels for teaching
// (student can load via csaLoadMap)
static inline void csaMapAll(uint32_t* lo, uint32_t* hi) {
  *lo = 0xFFFFFFFFu;
  *hi = 0x1Fu;
}

// Avoid BLE channels that sit under Wi-Fi 1/6/11 energy (rough educational mask)
// Wi-Fi ch1 ~ nRF12, ch6 ~37, ch11 ~62 → BLE data near those MHz
static inline void csaMapAvoidWifi1611(uint32_t* lo, uint32_t* hi) {
  csaMapAll(lo, hi);
  // Clear a band of data channels around overlapping regions (approx)
  // BLE k → MHz 2402+2k; clear k where 2402+2k in [2407..2427] U [2432..2452] U [2457..2477]
  for (int k = 0; k < 37; k++) {
    int mhz = 2402 + 2 * k;
    bool bad = (mhz >= 2407 && mhz <= 2427) || (mhz >= 2432 && mhz <= 2452) ||
               (mhz >= 2457 && mhz <= 2477);
    if (bad) {
      if (k < 32) *lo &= ~(1u << k);
      else *hi &= ~(1u << (k - 32));
    }
  }
  // Ensure at least 2 channels remain
  if (__builtin_popcount(*lo) + __builtin_popcount(*hi) < 2) csaMapAll(lo, hi);
}

static inline bool csaMapHas(uint32_t lo, uint32_t hi, uint8_t ch) {
  if (ch > 36) return false;
  if (ch < 32) return (lo >> ch) & 1u;
  return (hi >> (ch - 32)) & 1u;
}

static inline uint8_t csaMapCount(uint32_t lo, uint32_t hi) {
  return (uint8_t)(__builtin_popcount(lo) + __builtin_popcount(hi & 0x1Fu));
}

// Build ordered used-list from map
static inline uint8_t csaBuildUsed(uint32_t lo, uint32_t hi, uint8_t* used /*[37]*/) {
  uint8_t n = 0;
  for (uint8_t k = 0; k < 37; k++) {
    if (csaMapHas(lo, hi, k)) used[n++] = k;
  }
  return n;
}

// BLE data index 0..36 → nRF24 channel
static inline uint8_t bleDataToNrf(uint8_t bleDataCh) {
  if (bleDataCh > 36) bleDataCh = 36;
  return (uint8_t)(2 + 2 * bleDataCh);  // 2402+2k − 2400
}

// ---------- CSA #1 ----------
// unmapped = (prev + hopInc) % 37
// if unmapped not in map: remap = used[eventCounter % nUsed]
struct Csa1State {
  uint8_t  prev;          // last unmapped (0..36)
  uint8_t  hopInc;        // 5..16 typical odd values in real links; lab default 5
  uint16_t eventCounter;
  uint32_t mapLo, mapHi;
  uint8_t  used[37];
  uint8_t  nUsed;
};

static inline void csa1Init(Csa1State* s, uint8_t hopInc, uint32_t mapLo, uint32_t mapHi) {
  memset(s, 0, sizeof(*s));
  s->hopInc = hopInc ? hopInc : 5;
  s->mapLo = mapLo;
  s->mapHi = mapHi;
  s->nUsed = csaBuildUsed(mapLo, mapHi, s->used);
  if (s->nUsed == 0) {
    csaMapAll(&s->mapLo, &s->mapHi);
    s->nUsed = csaBuildUsed(s->mapLo, s->mapHi, s->used);
  }
  s->prev = 0;
  s->eventCounter = 0;
}

static inline uint8_t csa1NextNrf(Csa1State* s) {
  uint8_t unmapped = (uint8_t)((s->prev + s->hopInc) % 37);
  s->prev = unmapped;
  uint8_t ch = unmapped;
  if (!csaMapHas(s->mapLo, s->mapHi, unmapped)) {
    ch = s->used[s->eventCounter % s->nUsed];
  }
  s->eventCounter++;
  return bleDataToNrf(ch);
}

// ---------- CSA #2 (Core Spec–aligned educational) ----------
// Bluetooth Core Spec Vol 6 Part B — Channel Selection Algorithm #2
// Educational reconstruction of publicly documented steps:
//   1) prn_e from eventCounter + channelId (perm / mam ops)
//   2) unmapped = prn_e % 37
//   3) if unmapped ∉ map: remappingIndex = floor(N * prn_e / 2^16)
//      ch = used[remappingIndex]
// Not bit-identical silicon; good for lab period / map demos.
// Refs: Core Spec; open BLE stacks (Zephyr/NimBLE educational ports)
struct Csa2State {
  uint16_t eventCounter;
  uint16_t channelId;  // CI = AA[31:16] XOR AA[15:0]
  uint32_t mapLo, mapHi;
  uint8_t  used[37];
  uint8_t  nUsed;
};

// perm operation used in CSA#2 descriptions (bit shuffle)
static inline uint16_t csa2_perm(uint16_t x) {
  // Bit permutation matching common open-source CSA#2 teaching ports
  uint16_t r = 0;
  const uint8_t shuf[16] = {14, 11, 8, 12, 6, 2, 3, 15, 10, 9, 1, 7, 4, 13, 5, 0};
  for (int i = 0; i < 16; i++) {
    if (x & (1u << i)) r |= (uint16_t)(1u << shuf[i]);
  }
  return r;
}

// mam: multiply-add-modulo style step from CSA#2 literature
static inline uint16_t csa2_mam(uint16_t a, uint16_t b) {
  // (17 * a + b) mod 2^16 — educational form of MAM used in CSA#2 write-ups
  return (uint16_t)(17u * a + b);
}

// Generate prn_e for event counter e and channel identifier chId
static inline uint16_t csa2_prn_e(uint16_t e, uint16_t chId) {
  // Sequence mirrors Core Spec composition at educational fidelity:
  //   prn_e = perm( mam( perm(e XOR chId) , chId ) )
  uint16_t x = (uint16_t)(e ^ chId);
  x = csa2_perm(x);
  x = csa2_mam(x, chId);
  x = csa2_perm(x);
  return x;
}

static inline void csa2Init(Csa2State* s, uint16_t channelId, uint32_t mapLo, uint32_t mapHi) {
  memset(s, 0, sizeof(*s));
  s->channelId = channelId ? channelId : 0xA5C3;
  s->mapLo = mapLo;
  s->mapHi = mapHi;
  s->nUsed = csaBuildUsed(mapLo, mapHi, s->used);
  if (s->nUsed == 0) {
    csaMapAll(&s->mapLo, &s->mapHi);
    s->nUsed = csaBuildUsed(s->mapLo, s->mapHi, s->used);
  }
  s->eventCounter = 0;
}

static inline uint8_t csa2NextNrf(Csa2State* s) {
  uint16_t e = s->eventCounter++;
  uint16_t prn = csa2_prn_e(e, s->channelId);
  uint8_t unmapped = (uint8_t)(prn % 37);
  uint8_t ch = unmapped;
  if (!csaMapHas(s->mapLo, s->mapHi, unmapped) && s->nUsed > 0) {
    // Core Spec remap: remappingIndex = floor(N * prn_e / 65536)
    uint8_t idx = (uint8_t)(((uint32_t)s->nUsed * (uint32_t)prn) >> 16);
    if (idx >= s->nUsed) idx = (uint8_t)(s->nUsed - 1);
    ch = s->used[idx];
  }
  return bleDataToNrf(ch);
}

static inline const char* csaMapName(int id) {
  switch (id) {
    case 1: return "avoid-wifi-1-6-11";
    default: return "all-37-data";
  }
}
