#pragma once
#include <stdint.h>

#define LAB_NOW_MAGIC 0x4C414255u

enum LabNowType : uint8_t {
  LABNOW_BEACON = 1,
  LABNOW_MARKER = 2,
  LABNOW_MODE   = 3,
  LABNOW_ARM    = 4,
  LABNOW_CMD    = 5,
  LABNOW_ACK    = 6,
};

enum LabNowCmd : uint8_t {
  LABCMD_SET_CH = 1,
  LABCMD_REQ_FIXED = 2,
  LABCMD_MARKER = 3,
  LABCMD_ARM = 4,
  LABCMD_DISARM = 5,
};

#pragma pack(push, 1)
struct LabNowPkt {
  uint32_t magic;
  uint32_t seq;
  uint32_t t_ms;
  uint8_t  type;
  uint8_t  mode;
  uint8_t  chH;
  uint8_t  chV;
  uint8_t  armed;
  uint8_t  hopRate;
  uint16_t uniqueApprox;
  float    rpdPct;
  char     tag[8];
};
#pragma pack(pop)
