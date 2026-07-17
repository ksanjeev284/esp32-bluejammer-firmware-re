#pragma once
// Exact UTF-8 serial lines from original firmware DROM
#include <Arduino.h>
namespace OrigSerialArt {
  // 0x3F400120 len=132
  static const char S00[] PROGMEM = u8"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
  // 0x3F4001A5 len=38
  static const char S01[] PROGMEM = u8"╦ ╦╔═╗╔═╗╦       ╔═╗╦ ╦╔═╗╔═╗╔═╗╔═╗╔═╗";
  // 0x3F400206 len=38
  static const char S02[] PROGMEM = u8"╠═╣╚═╗╠═╝║  ───  ╚═╗║ ║║  ║  ║╣ ╚═╗╚═╗";
  // 0x3F400265 len=38
  static const char S03[] PROGMEM = u8"╩ ╩╚═╝╩  ╩       ╚═╝╚═╝╚═╝╚═╝╚═╝╚═╝╚═╝";
  // 0x3F4002C4 len=153
  static const char S04[] PROGMEM = u8"Hardware Serial Peripheral Interface started !!! HSPI nRF24 module initialized SUCCESSFULLY! ############################################################";
  // 0x3F40035E len=33
  static const char S05[] PROGMEM = u8"╦ ╦╔═╗╔═╗╦       ╔═╗╔═╗╦╦  ╔═╗╔╦╗";
  // 0x3F4003AE len=33
  static const char S06[] PROGMEM = u8"╠═╣╚═╗╠═╝║  ───  ╠╣ ╠═╣║║  ║╣  ║║";
  // 0x3F400400 len=33
  static const char S07[] PROGMEM = u8"╩ ╩╚═╝╩  ╩       ╚  ╩ ╩╩╩═╝╚═╝═╩╝";
  // 0x3F40044A len=153
  static const char S08[] PROGMEM = u8"!!! Hardware Serial Peripheral Interface start failure! HSPI nRF24 module could NOT be initialized! #####################################################";
  // 0x3F4004E4 len=39
  static const char S09[] PROGMEM = u8"╦  ╦╔═╗╔═╗╦       ╔═╗╦ ╦╔═╗╔═╗╔═╗╔═╗╔═╗";
  // 0x3F400546 len=39
  static const char S10[] PROGMEM = u8"╚╗╔╝╚═╗╠═╝║  ───  ╚═╗║ ║║  ║  ║╣ ╚═╗╚═╗";
  // 0x3F4005A8 len=39
  static const char S11[] PROGMEM = u8" ╚╝ ╚═╝╩  ╩       ╚═╝╚═╝╚═╝╚═╝╚═╝╚═╝╚═╝";
  // 0x3F400608 len=153
  static const char S12[] PROGMEM = u8"Variable Serial Peripheral Interface started !!! VSPI nRF24 module initialized SUCCESSFULLY! ############################################################";
  // 0x3F4006A2 len=34
  static const char S13[] PROGMEM = u8"╦  ╦╔═╗╔═╗╦       ╔═╗╔═╗╦╦  ╔═╗╔╦╗";
  // 0x3F4006F3 len=34
  static const char S14[] PROGMEM = u8"╚╗╔╝╚═╗╠═╝║  ───  ╠╣ ╠═╣║║  ║╣  ║║";
  // 0x3F400748 len=34
  static const char S15[] PROGMEM = u8" ╚╝ ╚═╝╩  ╩       ╚  ╩ ╩╩╩═╝╚═╝═╩╝";
  // 0x3F400793 len=153
  static const char S16[] PROGMEM = u8"!!! Variable Serial Peripheral Interface start failure! VSPI nRF24 module could NOT be initialized! #####################################################";
  // 0x3F400838 len=132
  static const char S17[] PROGMEM = u8"####################################################################################################################################";
  // 0x3F4008BD len=160
  static const char S18[] PROGMEM = u8"âââââââ âââââââ ââââââ  ââââââ  ââââââ        ââââââ  ââ      ââ    ââ â";
  // 0x3F4009E8 len=160
  static const char S19[] PROGMEM = u8"ââ      ââ      ââ   ââ      ââ      ââ       ââ   ââ ââ      ââ    ââ ââ           ââ ââ   ââ ââ";
  // 0x3F400AD5 len=70
  static const char S20[] PROGMEM = u8"█████   ███████ ██████   █████   █████  █████ ██████  ██      ██    ██";
  // 0x3F400C06 len=160
  static const char S21[] PROGMEM = u8"ââ           ââ ââ           ââ ââ            ââ   ââ ââ      ââ    ââ ââ      ââ   ââ ââ   ââ ââ";
  // 0x3F400CEB len=160
  static const char S22[] PROGMEM = u8"âââââââ âââââââ ââ      ââââââ  âââââââ       ââââââ  âââââââ  âââââ";
  // 0x3F400E16 len=132
  static const char S23[] PROGMEM = u8"                                          Firmware : Combo-Channel-Select (BT-BLE-WiFi-RC)                                          ";
  // 0x3F400E9B len=78
  static const char S24[] PROGMEM = u8"                        ██████╗ ██╗   ██╗    ███████╗███╗   ███╗███████╗███╗  ";
  // 0x3F400FA6 len=160
  static const char S25[] PROGMEM = u8"                        ââââââââââââ ââââ    âââââââââââââ âââââââââââââââ";
  // 0x3F4010C1 len=76
  static const char S26[] PROGMEM = u8"                        ██████╔╝ ╚████╔╝     █████╗  ██╔████╔██║█████╗  ██╔█";
  // 0x3F4011CA len=160
  static const char S27[] PROGMEM = u8"                        ââââââââ  âââââ      ââââââ  âââââââââââââââââ  ââââââ";
  // 0x3F4012D1 len=78
  static const char S28[] PROGMEM = u8"                        ██████╔╝   ██║       ███████╗██║ ╚═╝ ██║███████╗██║ ╚█";
  // 0x3F4013D2 len=160
  static const char S29[] PROGMEM = u8"                        âââââââ    âââ       âââââââââââ     ââââââââââââââ  âââââ";
  // 0x3F4014C9 len=132
  static const char S30[] PROGMEM = u8"                                                    !Educational purposes only!                                                     ";
  // 0x3F40154E len=132
  static const char S31[] PROGMEM = u8"                                         https://github.com/EmenstaNougat/ESP32-BlueJammer                                          ";
  // 0x3F4015D3 len=132
  static const char S32[] PROGMEM = u8"                                               I'm not responsible for your actions!                                                ";
  inline void printHSPISuccess() {
    Serial.println(S01);
    Serial.println(S02);
    Serial.println(S03);
    Serial.println(S04);
  }
  inline void printHSPIFail() {
    Serial.println(S05);
    Serial.println(S06);
    Serial.println(S07);
    Serial.println(S08);
  }
  inline void printVSPISuccess() {
    Serial.println(S09);
    Serial.println(S10);
    Serial.println(S11);
    Serial.println(S12);
  }
  inline void printVSPIFail() {
    Serial.println(S13);
    Serial.println(S14);
    Serial.println(S15);
    Serial.println(S16);
  }
  inline void printBootBanner() {
    Serial.println(S17);
    Serial.println(S18);
    Serial.println(S19);
    Serial.println(S20);
    Serial.println(S21);
    Serial.println(S22);
    Serial.println(S23);
    Serial.println(S24);
    Serial.println(S25);
    Serial.println(S26);
    Serial.println(S27);
    Serial.println(S28);
    Serial.println(S29);
    Serial.println(S30);
    Serial.println(S31);
    Serial.println(S32);
  }
  inline void printSep() { Serial.println(S00); }
} // namespace OrigSerialArt
