#pragma once
/*
 * Experiment sequencer — timed playlist of modes / fixed channels
 * Mode ST_EXP runs steps until loop or pause.
 */

#include <stdint.h>

struct ExpStep {
  uint8_t  mode;       // ST_* (7=FIXED uses chH/chV)
  uint16_t durationMs; // step length
  uint8_t  chH;        // for FIXED
  uint8_t  chV;
  char     tag[6];     // short label for serial/CSV
};

// Default lab playlist: map tour → fixed carriers → CSA demos
static const ExpStep kDefaultExperiment[] = {
    {1,  8000, 0,  0,  "BT"},      // BT
    {2,  8000, 0,  0,  "BLE"},     // BLE map
    {3,  8000, 0,  0,  "WIFI"},    // 802.11
    {7, 10000, 45, 55, "FIX"},     // FIXED range-friendly
    {9, 10000, 0,  0,  "CSA1"},    // CSA#1
    {10,10000, 0,  0,  "CSA2"},    // CSA#2
    {8, 12000, 0,  0,  "SLOW"},    // slow sweep SDR
    {6, 10000, 0,  0,  "COEX"},    // coexist
};

static const uint8_t kDefaultExperimentN =
    (uint8_t)(sizeof(kDefaultExperiment) / sizeof(kDefaultExperiment[0]));

// Range A/B playlist
static const ExpStep kRangeExperiment[] = {
    {7, 15000, 45, 55, "R45"},
    {7, 15000, 2,  26, "RADV"},
    {7, 15000, 12, 37, "RW1"},
    {7, 15000, 37, 62, "RW6"},
};
static const uint8_t kRangeExperimentN =
    (uint8_t)(sizeof(kRangeExperiment) / sizeof(kRangeExperiment[0]));

struct ExpRunner {
  const ExpStep* steps;
  uint8_t n;
  uint8_t idx;
  uint32_t stepStartMs;
  bool running;
  bool loopPlaylist;
};

static inline void expInit(ExpRunner* r, const ExpStep* steps, uint8_t n, bool loop) {
  r->steps = steps;
  r->n = n;
  r->idx = 0;
  r->stepStartMs = 0;
  r->running = false;
  r->loopPlaylist = loop;
}

static inline void expStart(ExpRunner* r, uint32_t now) {
  r->idx = 0;
  r->stepStartMs = now;
  r->running = r->n > 0;
}

static inline void expStop(ExpRunner* r) { r->running = false; }

// Returns true if step changed
static inline bool expTick(ExpRunner* r, uint32_t now, uint8_t* outMode, uint8_t* outH,
                           uint8_t* outV, const char** outTag) {
  if (!r->running || !r->steps || r->n == 0) return false;
  const ExpStep* s = &r->steps[r->idx];
  *outMode = s->mode;
  *outH = s->chH;
  *outV = s->chV;
  *outTag = s->tag;
  if (now - r->stepStartMs >= s->durationMs) {
    r->idx++;
    if (r->idx >= r->n) {
      if (r->loopPlaylist) r->idx = 0;
      else {
        r->running = false;
        r->idx = (uint8_t)(r->n - 1);
        return true;
      }
    }
    r->stepStartMs = now;
    s = &r->steps[r->idx];
    *outMode = s->mode;
    *outH = s->chH;
    *outV = s->chV;
    *outTag = s->tag;
    return true;
  }
  return false;
}
