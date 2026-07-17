#pragma once
/*
 * ESP-NOW lab sync packets (TX ↔ RangeObserver) v0.5 bidirectional
 * Magic LABU = 0x4C414255
 */

#include <stdint.h>

#define LAB_NOW_MAGIC 0x4C414255u

enum LabNowType : uint8_t {
  LABNOW_BEACON = 1,   // TX → OBS periodic stats
  LABNOW_MARKER = 2,   // TX → OBS distance marker
  LABNOW_MODE   = 3,   // TX → OBS mode change
  LABNOW_ARM    = 4,   // TX → OBS arm/disarm
  LABNOW_CMD    = 5,   // OBS → TX command (see cmd field in tag[0] or mode)
  LABNOW_ACK    = 6,   // OBS → TX marker ack with RPD in rpdPct
};

// CMD codes stored in pkt.mode when type==LABNOW_CMD
enum LabNowCmd : uint8_t {
  LABCMD_SET_CH = 1,     // chH = channel for FIXED follow
  LABCMD_REQ_FIXED = 2,  // request TX enter FIXED on chH/chV
  LABCMD_MARKER = 3,     // remote marker request
  LABCMD_ARM = 4,        // remote arm (lab only)
  LABCMD_DISARM = 5,
};

#pragma pack(push, 1)
struct LabNowPkt {
  uint32_t magic;
  uint32_t seq;
  uint32_t t_ms;
  uint8_t  type;
  uint8_t  mode;   // mode or LabNowCmd
  uint8_t  chH;
  uint8_t  chV;
  uint8_t  armed;
  uint8_t  hopRate;
  uint16_t uniqueApprox;
  float    rpdPct;
  char     tag[8];
};
#pragma pack(pop)
