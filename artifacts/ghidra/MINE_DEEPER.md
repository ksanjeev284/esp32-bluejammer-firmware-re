# Mine deeper — 89 functions

## RF24 / peripheral rename map

| VA | Suggested name |
|---:|---|
| `0x400d3034` | `nrf_writeRegister` |
| `0x400d2fcc` | `nrf_readRegister` |
| `0x400d2f90` | `nrf_writeCmd` |
| `0x400d2ff8` | `nrf_writeBytes` |
| `0x400d2f60` | `nrf_csnLow` |
| `0x400d2f7c` | `nrf_csnHigh` |
| `0x400d2f4c` | `nrf_ce` |
| `0x400d2f38` | `nrf_csn` |
| `0x400d3060` | `nrf_flushRx` |
| `0x400d3078` | `nrf_flushTx` |
| `0x400d30f0` | `nrf_setPayloadSize` |
| `0x400d3248` | `nrf_setAddressWidth` |
| `0x400d30d8` | `nrf_setChannel` |
| `0x400d32f4` | `nrf_setPALevel` |
| `0x400d3328` | `nrf_setDataRate` |
| `0x400d3460` | `nrf_setCRCLength` |
| `0x400d34b0` | `nrf_setRetries` |
| `0x400d32c4` | `nrf_stopListening` |
| `0x400d3180` | `nrf_startListening_or_openPipe` |
| `0x400d34d8` | `nrf_startConstCarrier` |
| `0x400d3590` | `nrf_stopConstCarrier` |
| `0x400d31d8` | `nrf_powerDown` |
| `0x400d31fc` | `nrf_powerUp` |
| `0x400d3448` | `nrf_begin` |
| `0x400d337c` | `nrf_begin_chipInit` |
| `0x400d3120` | `nrf_isChipConnected` |
| `0x400d5e80` | `randomChannel` |
| `0x400d670c` | `millis` |
| `0x400d6724` | `delay_ms` |
| `0x400d6730` | `delayMicroseconds` |
| `0x400d6224` | `digitalRead` |
| `0x400d6214` | `digitalWrite` |
| `0x400d6198` | `pinMode` |
| `0x400d5d30` | `Serial_print` |
| `0x400d5d1c` | `Serial_println` |
| `0x400d51fc` | `display_clearDisplay` |
| `0x400d56b4` | `display_display` |
| `0x400d4fd8` | `display_setTextSize` |
| `0x400d5d08` | `display_print` |

## `radioTask` @ `400d236c` (see decomp_mine/)


## `FUN_400d2714` @ `400d2714` (see decomp_mine/)


## `FUN_400d2bfc` @ `400d2bfc` (see decomp_mine/)


## `FUN_400d2d68` @ `400d2d68`
```c

void FUN_400d2d68(void)

{
  int iVar1;
  int iVar2;
  
  FUN_400d493c(DAT_400d018c,4,5,0);
  iVar1 = DAT_400d0144;
  iVar2 = FUN_400d5220(DAT_400d0144,2,0x3c,1);
  if (iVar2 == 0) {
    Serial_print(DAT_400d0028,PTR_str_SSD1306_alloc_failed_400d0190);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  FUN_400d51fc(iVar1);
  *(undefined4 *)(iVar1 + 0x14) = DAT_400d0194;
  FUN_400d56b4(iVar1);
  return;
}


```


## `FUN_400d2dac` @ `400d2dac` (see decomp_mine/)


## `FUN_400d2f0c` @ `400d2f0c`
```c

void FUN_400d2f0c(void)

{
  FUN_400d5014(DAT_400d0144,0x80,0x40,DAT_400d018c,0xffffffff,DAT_400d01c8,DAT_400d01cc);
  return;
}


```


## `FUN_400d2f2c` @ `400d2f2c`
```c

void FUN_400d2f2c(void)

{
  FUN_400d4fec(DAT_400d0144);
  return;
}


```


## `nrf_csn` @ `400d2f38`
```c

void FUN_400d2f38(int param_1,undefined1 param_2)

{
  gpio_write_or_mode(*(undefined1 *)(param_1 + 5),param_2);
  FUN_400d6730(*(undefined4 *)(param_1 + 0x24));
  return;
}


```


## `nrf_ce` @ `400d2f4c`
```c

void FUN_400d2f4c(int param_1,undefined1 param_2)

{
  if (*(char *)(param_1 + 5) != *(char *)(param_1 + 4)) {
    gpio_write_or_mode(*(char *)(param_1 + 4),param_2);
  }
  return;
}


```


## `nrf_csnLow` @ `400d2f60`
```c

void FUN_400d2f60(undefined4 *param_1)

{
  FUN_400d3730(*param_1,param_1[2],1);
  nrf_csn(param_1,0);
  return;
}


```


## `nrf_csnHigh` @ `400d2f7c`
```c

void FUN_400d2f7c(undefined4 *param_1)

{
  nrf_csn(param_1,1);
  FUN_400d3778(*param_1);
  return;
}


```


## `nrf_writeCmd` @ `400d2f90`
```c

void FUN_400d2f90(undefined4 *param_1,undefined1 param_2,undefined1 *param_3,char param_4)

{
  undefined1 uVar1;
  
  nrf_csnLow(param_1);
  uVar1 = FUN_400d379c(*param_1,param_2);
  *(undefined1 *)(param_1 + 3) = uVar1;
  while (param_4 = param_4 + -1, param_4 != -1) {
    uVar1 = FUN_400d379c(*param_1,0xff);
    *param_3 = uVar1;
    param_3 = param_3 + 1;
  }
  nrf_csnHigh(param_1);
  return;
}


```


## `nrf_readRegister` @ `400d2fcc`
```c

undefined4 FUN_400d2fcc(undefined4 *param_1,undefined1 param_2)

{
  undefined1 uVar1;
  undefined4 uVar2;
  
  nrf_csnLow(param_1);
  uVar1 = FUN_400d379c(*param_1,param_2);
  *(undefined1 *)(param_1 + 3) = uVar1;
  uVar2 = FUN_400d379c(*param_1,0xff);
  nrf_csnHigh(param_1);
  return uVar2;
}


```


## `nrf_writeBytes` @ `400d2ff8`
```c

void FUN_400d2ff8(undefined4 *param_1,byte param_2,undefined1 *param_3,char param_4)

{
  undefined1 uVar1;
  
  nrf_csnLow(param_1);
  uVar1 = FUN_400d379c(*param_1,param_2 | 0x20);
  *(undefined1 *)(param_1 + 3) = uVar1;
  while (param_4 = param_4 + -1, param_4 != -1) {
    uVar1 = *param_3;
    param_3 = param_3 + 1;
    FUN_400d379c(*param_1,uVar1);
  }
  nrf_csnHigh(param_1);
  return;
}


```


## `nrf_writeRegister` @ `400d3034`
```c

void FUN_400d3034(undefined4 *param_1,byte param_2,undefined1 param_3)

{
  undefined1 uVar1;
  
  nrf_csnLow(param_1);
  uVar1 = FUN_400d379c(*param_1,param_2 | 0x20);
  *(undefined1 *)(param_1 + 3) = uVar1;
  FUN_400d379c(*param_1,param_3);
  nrf_csnHigh(param_1);
  return;
}


```


## `nrf_flushRx` @ `400d3060`
```c

undefined1 FUN_400d3060(int param_1)

{
  nrf_writeCmd(param_1,0xe2,0);
  return *(undefined1 *)(param_1 + 0xc);
}


```


## `nrf_flushTx` @ `400d3078`
```c

undefined1 FUN_400d3078(int param_1)

{
  nrf_writeCmd(param_1,0xe1,0);
  return *(undefined1 *)(param_1 + 0xc);
}


```


## `FUN_400d3090` @ `400d3090`
```c

void FUN_400d3090(undefined4 *param_1)

{
  uint uVar1;
  
  uVar1 = DAT_400d01d0;
  *param_1 = DAT_400d0020;
  if ((uint)param_1[2] <= uVar1) {
    param_1[2] = DAT_400d01d4;
  }
  return;
}


```


## `FUN_400d30a8` @ `400d30a8`
```c

void FUN_400d30a8(int param_1,undefined1 param_2,undefined1 param_3,undefined4 param_4)

{
  *(undefined1 *)(param_1 + 0xd) = 0x20;
  *(undefined1 *)(param_1 + 0x19) = 0;
  *(undefined1 *)(param_1 + 0x1a) = 0;
  *(undefined1 *)(param_1 + 0x1e) = 0;
  *(undefined1 *)(param_1 + 4) = param_2;
  *(undefined1 *)(param_1 + 5) = param_3;
  *(undefined4 *)(param_1 + 8) = param_4;
  *(undefined2 *)(param_1 + 0x1c) = 0x105;
  *(undefined4 *)(param_1 + 0x24) = 5;
  FUN_400d3090(param_1);
  return;
}


```


## `nrf_setChannel` @ `400d30d8`
```c

void nrf_setChannel(undefined4 param_1,byte param_2)

{
  if (0x7c < param_2) {
    param_2 = 0x7d;
  }
  nrf_writeRegister(param_1,5,param_2);
  return;
}


```


## `nrf_setPayloadSize` @ `400d30f0`
```c

void FUN_400d30f0(int param_1,byte param_2)

{
  int iVar1;
  int iVar2;
  char cVar3;
  
  cVar3 = '\x01';
  if (param_2 != 0) {
    cVar3 = (param_2 < 0x20) * param_2 + (param_2 >= 0x20) * ' ';
  }
  *(char *)(param_1 + 0xd) = cVar3;
  iVar1 = 0x11;
  do {
    iVar2 = iVar1 + 1;
    nrf_writeRegister(param_1,iVar1,*(undefined1 *)(param_1 + 0xd));
    iVar1 = iVar2;
  } while (iVar2 != 0x17);
  return;
}


```


## `nrf_isChipConnected` @ `400d3120`
```c

bool nrf_isChipConnected(int param_1)

{
  int iVar1;
  
  iVar1 = nrf_readRegister(param_1,3);
  return *(byte *)(param_1 + 0x1c) - 2 == iVar1;
}


```


## `FUN_400d3144` @ `400d3144`
```c

int FUN_400d3144(int param_1)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_FUN_400d01d8)(param_1);
  if (iVar1 != 0) {
    if (*(char *)(param_1 + 5) != *(char *)(param_1 + 4)) {
      FUN_400d6198(*(char *)(param_1 + 4),3);
      FUN_400d6198(*(undefined1 *)(param_1 + 5),3);
    }
    nrf_ce(param_1,0);
    nrf_csn(param_1,1);
  }
  return iVar1;
}


```


## `nrf_startListening_or_openPipe` @ `400d3180`
```c

void FUN_400d3180(int param_1)

{
  byte bVar1;
  
  nrf_ce(param_1,0);
  FUN_400d6730(*(undefined4 *)(param_1 + 0x20));
  if (*(char *)(param_1 + 0x1b) != '\0') {
    nrf_flushTx(param_1);
  }
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfe;
  nrf_writeRegister(param_1,0);
  nrf_writeBytes(param_1,10,param_1 + 0x13,*(undefined1 *)(param_1 + 0x1c));
  bVar1 = nrf_readRegister(param_1,2);
  nrf_writeRegister(param_1,2,bVar1 | 1);
  return;
}


```


## `nrf_powerDown` @ `400d31d8`
```c

void FUN_400d31d8(int param_1)

{
  nrf_ce(param_1,0);
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfd;
  nrf_writeRegister(param_1,0);
  return;
}


```


## `nrf_powerUp` @ `400d31fc`
```c

void FUN_400d31fc(int param_1)

{
  if ((*(byte *)(param_1 + 0x18) & 2) == 0) {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) | 2;
    nrf_writeRegister(param_1);
    FUN_400d6730(DAT_400d01dc);
  }
  return;
}


```


## `FUN_400d3220` @ `400d3220`
```c

void FUN_400d3220(undefined4 param_1)

{
  nrf_ce(param_1,0);
  nrf_writeRegister(param_1,7,0x10);
  nrf_writeCmd(param_1,0xe3,0);
  nrf_ce(param_1,1);
  return;
}


```


## `nrf_setAddressWidth` @ `400d3248`
```c

void FUN_400d3248(int param_1,char param_2)

{
  byte bVar1;
  
  if ((byte)(param_2 - 2U) == 0) {
    nrf_writeRegister(param_1,3);
    *(undefined1 *)(param_1 + 0x1c) = 2;
  }
  else {
    bVar1 = param_2 - 2U & 3;
    nrf_writeRegister(param_1,3,bVar1);
    *(byte *)(param_1 + 0x1c) = bVar1 + 2;
  }
  return;
}


```


## `FUN_400d327c` @ `400d327c`
```c

void FUN_400d327c(undefined4 *param_1)

{
  undefined1 uVar1;
  
  nrf_csnLow(param_1);
  uVar1 = FUN_400d379c(*param_1,0x50);
  *(undefined1 *)(param_1 + 3) = uVar1;
  FUN_400d379c(*param_1,0x73);
  nrf_csnHigh(param_1);
  return;
}


```


## `FUN_400d32a0` @ `400d32a0`
```c

void FUN_400d32a0(int param_1)

{
  uint uVar1;
  
  if (*(char *)(param_1 + 0x1b) != '\0') {
    uVar1 = nrf_readRegister(param_1,0x1d);
    nrf_writeRegister(param_1,0x1d,uVar1 & 0xfd);
    *(undefined1 *)(param_1 + 0x1b) = 0;
  }
  return;
}


```


## `nrf_stopListening` @ `400d32c4`
```c

void FUN_400d32c4(int param_1,char param_2)

{
  if (param_2 == '\0') {
    nrf_writeRegister(param_1,1);
    if (*(char *)(param_1 + 0x1b) != '\0') {
      FUN_400d32a0(param_1);
    }
  }
  else {
    nrf_writeRegister(param_1,1,0x3f);
  }
  return;
}


```


## `nrf_setPALevel` @ `400d32f4`
```c

void FUN_400d32f4(undefined4 param_1,byte param_2,char param_3)

{
  byte bVar1;
  
  bVar1 = nrf_readRegister(param_1,6);
  nrf_writeRegister(param_1,6,
                    bVar1 & 0xf8 |
                    param_3 + ((param_2 < 3) * param_2 + (param_2 >= 3) * '\x03') * '\x02');
  return;
}


```


## `nrf_setDataRate` @ `400d3328`
```c

bool FUN_400d3328(int param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = nrf_readRegister(param_1,6);
  if (param_2 == 2) {
    *(undefined4 *)(param_1 + 0x20) = 0x1f9;
    uVar2 = 0x20;
  }
  else if (param_2 == 1) {
    *(undefined4 *)(param_1 + 0x20) = 0xf0;
    uVar2 = 8;
  }
  else {
    *(undefined4 *)(param_1 + 0x20) = 0x118;
    uVar2 = 0;
  }
  uVar2 = uVar1 & 0xd7 | uVar2;
  nrf_writeRegister(param_1,6,uVar2);
  uVar1 = nrf_readRegister(param_1,6);
  return uVar2 == uVar1;
}


```


## `nrf_begin_chipInit` @ `400d337c`
```c

bool FUN_400d337c(int param_1)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  
  delay_ms(5);
  nrf_writeRegister(param_1,4,0x5f);
  nrf_setDataRate(param_1,0);
  iVar2 = nrf_readRegister(param_1,0x1d);
  FUN_400d327c(param_1);
  iVar3 = nrf_readRegister(param_1,0x1d);
  *(bool *)(param_1 + 0x19) = iVar2 == iVar3;
  if (iVar3 != 0) {
    if (iVar2 == iVar3) {
      FUN_400d327c(param_1);
    }
    nrf_writeRegister(param_1,0x1d,0);
  }
  *(undefined1 *)(param_1 + 0x1b) = 0;
  nrf_writeRegister(param_1,0x1c,0);
  *(undefined1 *)(param_1 + 0x1d) = 0;
  nrf_writeRegister(param_1,1,0x3f);
  nrf_writeRegister(param_1,2,3);
  nrf_setPayloadSize(param_1,0x20);
  nrf_setAddressWidth(param_1,5);
  nrf_setChannel(param_1,0x4c);
  nrf_writeRegister(param_1,7,0x70);
  nrf_flushRx(param_1);
  nrf_flushTx(param_1);
  nrf_writeRegister(param_1,0,0xc);
  uVar1 = nrf_readRegister(param_1,0);
  *(undefined1 *)(param_1 + 0x18) = uVar1;
  nrf_powerUp(param_1);
  return *(char *)(param_1 + 0x18) == '\x0e';
}


```


## `nrf_begin` @ `400d3448`
```c

undefined4 nrf_begin(undefined4 *param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  *param_1 = param_2;
  iVar1 = FUN_400d3144(param_1);
  uVar2 = 0;
  if (iVar1 != 0) {
    uVar2 = nrf_begin_chipInit(param_1);
  }
  return uVar2;
}


```


## `nrf_setCRCLength` @ `400d3460`
```c

void FUN_400d3460(int param_1,int param_2)

{
  byte bVar1;
  byte bVar2;
  
  bVar2 = *(byte *)(param_1 + 0x18) & 0xf3;
  if (param_2 != 0) {
    if (param_2 == 1) {
      bVar1 = 8;
    }
    else {
      bVar1 = 0xc;
    }
    bVar2 = bVar2 | bVar1;
  }
  *(byte *)(param_1 + 0x18) = bVar2;
  nrf_writeRegister(param_1,0,*(undefined1 *)(param_1 + 0x18));
  return;
}


```


## `FUN_400d3494` @ `400d3494`
```c

void FUN_400d3494(int param_1)

{
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xf7;
  nrf_writeRegister(param_1,0);
  return;
}


```


## `nrf_setRetries` @ `400d34b0`
```c

void FUN_400d34b0(undefined4 param_1,byte param_2,byte param_3)

{
  nrf_writeRegister(param_1,4,
                    ((param_2 < 0xf) * param_2 + (param_2 >= 0xf) * '\x0f') * '\x10' |
                    (param_3 < 0xf) * param_3 + (param_3 >= 0xf) * '\x0f');
  return;
}


```


## `nrf_startConstCarrier` @ `400d34d8`
```c

void nrf_startConstCarrier(int param_1,undefined1 param_2,undefined1 param_3)

{
  int *piVar1;
  byte bVar2;
  undefined1 local_44 [32];
  int iStack_24;
  
  piVar1 = DAT_400d0130;
  memw();
  iStack_24 = *DAT_400d0130;
  memw();
  nrf_startListening_or_openPipe(param_1);
  bVar2 = nrf_readRegister(param_1,6);
  nrf_writeRegister(param_1,6,bVar2 | 0x90);
  if (*(char *)(param_1 + 0x19) != '\0') {
    nrf_stopListening(param_1,0);
    nrf_writeRegister(param_1,4,0);
    local_44[0] = 0xff;
    nrf_writeBytes(param_1,0x10,local_44,5);
    nrf_flushTx(param_1);
    nrf_writeBytes(param_1,0xa0,local_44,0x20);
    FUN_400d3494(param_1);
  }
  nrf_setPALevel(param_1,param_2,1);
  nrf_setChannel(param_1,param_3);
  nrf_ce(param_1,1);
  if (*(char *)(param_1 + 0x19) != '\0') {
    delay_ms(1);
    FUN_400d3220(param_1);
  }
  memw();
  memw();
  if (iStack_24 != *piVar1) {
    FUN_40082e5c();
  }
  return;
}


```


## `nrf_stopConstCarrier` @ `400d3590`
```c

void FUN_400d3590(int param_1)

{
  uint uVar1;
  
  nrf_powerDown(param_1);
  uVar1 = nrf_readRegister(param_1,6);
  nrf_writeRegister(param_1,6,uVar1 & 0x6f);
  nrf_ce(param_1,0);
  nrf_flushTx(param_1);
  if (*(char *)(param_1 + 0x19) != '\0') {
    nrf_writeBytes(param_1,0x10,param_1 + 0x13,*(undefined1 *)(param_1 + 0x1c));
  }
  return;
}


```


## `spi_setBus` @ `400d35d0`
```c

void spi_setBus(undefined1 *param_1,undefined1 param_2)

{
  undefined4 uVar1;
  
  *(undefined4 *)(param_1 + 8) = 0xffffff00;
  param_1[0xc] = 0xff;
  uVar1 = DAT_400d01e0;
  *param_1 = param_2;
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *(undefined4 *)(param_1 + 0x14) = uVar1;
  param_1[0x18] = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  uVar1 = FUN_40093e48(1);
  *(undefined4 *)(param_1 + 0x1c) = uVar1;
  return;
}


```


## `spi_setPins` @ `400d35fc` (see decomp_mine/)


## `FUN_400d36a4` @ `400d36a4`
```c

void FUN_400d36a4(int param_1,char param_2)

{
  if (param_2 == '\0') {
    if (*(char *)(param_1 + 8) != '\0') {
      FUN_400d6b3c(*(undefined4 *)(param_1 + 4));
      FUN_400d69e8(*(undefined4 *)(param_1 + 4),(int)*(char *)(param_1 + 0xc));
    }
  }
  else if (*(char *)(param_1 + 8) == '\0') {
    FUN_400d6a5c(*(undefined4 *)(param_1 + 4),0,(int)*(char *)(param_1 + 0xc));
    FUN_400d6af8(*(undefined4 *)(param_1 + 4));
  }
  *(char *)(param_1 + 8) = param_2;
  return;
}


```


## `FUN_400d36e4` @ `400d36e4`
```c

void FUN_400d36e4(int param_1)

{
  if (*(int *)(param_1 + 4) != 0) {
    FUN_400d6920(*(int *)(param_1 + 4),(int)*(char *)(param_1 + 9));
    FUN_400d6958(*(undefined4 *)(param_1 + 4),(int)*(char *)(param_1 + 10));
    FUN_400d69b0(*(undefined4 *)(param_1 + 4),(int)*(char *)(param_1 + 0xb));
    FUN_400d36a4(param_1,0);
    FUN_400d6ca4(*(undefined4 *)(param_1 + 4));
    *(undefined4 *)(param_1 + 4) = 0;
  }
  return;
}


```


## `FUN_400d371c` @ `400d371c`
```c

void FUN_400d371c(int param_1)

{
  FUN_400d36e4(param_1);
  if (*(int *)(param_1 + 0x1c) != 0) {
    FUN_40094454();
  }
  return;
}


```


## `FUN_400d3730` @ `400d3730`
```c

void FUN_400d3730(int param_1,int param_2,uint param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 uStack_23;
  
  do {
    iVar1 = FUN_40094190(*(undefined4 *)(param_1 + 0x1c),0xffffffff);
  } while (iVar1 != 1);
  iVar1 = (*(code *)PTR_FUN_400d01e4)(*(undefined4 *)(param_1 + 4));
  if ((*(int *)(param_1 + 0x14) != param_2) || (*(int *)(param_1 + 0x10) != iVar1)) {
    *(int *)(param_1 + 0x14) = param_2;
    uVar2 = FUN_400d7038(param_2);
    *(undefined4 *)(param_1 + 0x10) = uVar2;
  }
  uStack_23 = (undefined1)(param_3 >> 8);
  FUN_400d6efc(*(undefined4 *)(param_1 + 4),*(undefined4 *)(param_1 + 0x10),uStack_23,param_3 & 0xff
              );
  *(undefined1 *)(param_1 + 0x18) = 1;
  return;
}


```


## `FUN_400d3778` @ `400d3778`
```c

void FUN_400d3778(int param_1)

{
  if (*(char *)(param_1 + 0x18) != '\0') {
    *(undefined1 *)(param_1 + 0x18) = 0;
    FUN_400d6fc4(*(undefined4 *)(param_1 + 4));
    FUN_40093c38(*(undefined4 *)(param_1 + 0x1c),0,0);
  }
  return;
}


```


## `FUN_400d379c` @ `400d379c`
```c

undefined4 FUN_400d379c(int param_1,undefined1 param_2)

{
  undefined4 uVar1;
  
  if (*(char *)(param_1 + 0x18) == '\0') {
    uVar1 = FUN_400d6e80(*(undefined4 *)(param_1 + 4),param_2);
  }
  else {
    uVar1 = FUN_400d6fd8();
  }
  return uVar1;
}


```


## `FUN_400d37cc` @ `400d37cc`
```c

void FUN_400d37cc(void)

{
  FUN_400d371c(DAT_400d0020);
  return;
}


```


## `FUN_400d37d8` @ `400d37d8`
```c

void FUN_400d37d8(uint *param_1,uint param_2)

{
  uint uVar1;
  
  *param_1 = param_2;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  FUN_400d6198(param_2 & 0xff,5);
  uVar1 = FUN_400d6224((char)*param_1);
  param_1[4] = uVar1;
  uVar1 = FUN_400d6224((char)*param_1);
  param_1[5] = uVar1;
  uVar1 = FUN_400d6224((char)*param_1);
  param_1[6] = uVar1;
  param_1[8] = 0;
  return;
}


```


## `FUN_400d380c` @ `400d380c`
```c

void FUN_400d380c(undefined1 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  iVar1 = FUN_400d6224(*param_1);
  *(int *)(param_1 + 0x1c) = iVar1;
  if (*(int *)(param_1 + 0x18) != iVar1) {
    uVar2 = FUN_400d670c();
    *(undefined4 *)(param_1 + 0x20) = uVar2;
    *(undefined4 *)(param_1 + 0x18) = *(undefined4 *)(param_1 + 0x1c);
  }
  iVar1 = FUN_400d670c();
  if (*(uint *)(param_1 + 4) <= (uint)(iVar1 - *(int *)(param_1 + 0x20))) {
    *(undefined4 *)(param_1 + 0x10) = *(undefined4 *)(param_1 + 0x14);
    *(undefined4 *)(param_1 + 0x14) = *(undefined4 *)(param_1 + 0x1c);
  }
  iVar1 = *(int *)(param_1 + 0x10);
  iVar4 = *(int *)(param_1 + 0x14);
  if (iVar1 == iVar4) {
    return;
  }
  iVar3 = *(int *)(param_1 + 0xc);
  if (iVar3 != 2) {
    if (iVar3 == 0) {
      if (iVar1 != 1) {
        return;
      }
      if (iVar4 != 0) {
        return;
      }
    }
    else {
      if (iVar3 != 1 || iVar1 != 0) {
        return;
      }
      if (iVar4 != 1) {
        return;
      }
    }
  }
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 1;
  return;
}


```


## `FUN_400d38a0` @ `400d38a0`
```c

void FUN_400d38a0(void)

{
  undefined1 auStack_26 [3];
  undefined1 uStack_23;
  undefined1 uStack_22;
  undefined1 uStack_21;
  
  FUN_40126e88(0,auStack_26);
  (*(code *)PTR_FUN_400d01fc)
            (DAT_400d01f8,0x20,PTR_s__s_02X_02X_02X_400d01f4,PTR_s_esp32__400d01f0,uStack_23,
             uStack_22,uStack_21);
  return;
}


```


## `FUN_400d38cc` @ `400d38cc`
```c

int FUN_400d38cc(int param_1)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = 0;
  piVar2 = DAT_400d0200;
  while ((*piVar2 != param_1 || (*piVar2 == 0))) {
    iVar1 = iVar1 + 1;
    piVar2 = piVar2 + 1;
    if (iVar1 == 3) {
      return 3;
    }
  }
  return iVar1;
}


```


## `FUN_400d38e8` @ `400d38e8`
```c

undefined4 FUN_400d38e8(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = 0xffffffff;
  if (param_1 < 3) {
    uVar1 = FUN_400e4ef4(*(undefined4 *)(DAT_400d0200 + param_1 * 4),param_2);
  }
  return uVar1;
}


```


## `FUN_400d3908` @ `400d3908`
```c

int FUN_400d3908(int param_1)

{
  int iVar1;
  int aiStack_24 [9];
  
  if ((param_1 == 0) || (aiStack_24[0] = FUN_400987e4(0x90), aiStack_24[0] == 0)) {
    iVar1 = -1;
  }
  else {
    FUN_40090c10(aiStack_24[0],param_1,0x90);
    iVar1 = FUN_40093c38(*DAT_400d0204,aiStack_24,0xffffffff,0);
    iVar1 = -(uint)(iVar1 != 1);
  }
  return iVar1;
}


```


## `FUN_400d3b94` @ `400d3b94` (see decomp_mine/)


## `FUN_400d5000` @ `400d5000`
```c

void FUN_400d5000(undefined4 param_1)

{
  FUN_400d4fec(param_1);
  (*(code *)PTR_FUN_400d0088)(param_1);
  return;
}


```


## `FUN_400d5014` @ `400d5014`
```c

void FUN_400d5014(undefined4 *param_1,undefined1 param_2,undefined1 param_3,int param_4,
                 undefined1 param_5,undefined4 param_6,undefined4 param_7)

{
  undefined4 uVar1;
  
  FUN_400d4b7c(param_1,param_2,param_3);
  *param_1 = PTR_PTR_400d02f0;
  param_1[9] = 0;
  if (param_4 == 0) {
    param_4 = DAT_400d018c;
  }
  param_1[10] = param_4;
  *(undefined1 *)((int)param_1 + 0x33) = 0xff;
  *(undefined2 *)(param_1 + 0xd) = 0xffff;
  *(undefined1 *)((int)param_1 + 0x36) = 0xff;
  param_1[0xb] = 0;
  param_1[0xf] = param_7;
  uVar1 = DAT_400d01e0;
  *(undefined1 *)((int)param_1 + 0x37) = param_5;
  param_1[0x11] = uVar1;
  param_1[0xe] = param_6;
  *(undefined2 *)(param_1 + 0x12) = 1;
  return;
}


```


## `FUN_400d505c` @ `400d505c`
```c

void FUN_400d505c(int param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  
  param_2 = param_2 & 0xff;
  if (*(int *)(param_1 + 0x28) == 0) {
    gpio_write_or_mode(*(undefined1 *)(param_1 + 0x35),0);
    if (*(int *)(param_1 + 0x24) == 0) {
      iVar1 = 8;
      uVar2 = 0x80;
      do {
        gpio_write_or_mode(*(undefined1 *)(param_1 + 0x33),param_2 & uVar2);
        gpio_write_or_mode(*(undefined1 *)(param_1 + 0x34),1);
        iVar1 = iVar1 + -1;
        gpio_write_or_mode(*(undefined1 *)(param_1 + 0x34),0);
        uVar2 = uVar2 >> 1;
      } while (iVar1 != 0);
    }
    else {
      FUN_400d379c(*(int *)(param_1 + 0x24),param_2);
    }
  }
  else {
    FUN_400d4b2c(*(int *)(param_1 + 0x28),(int)*(char *)(param_1 + 0x30));
    (**(code **)(**(int **)(param_1 + 0x28) + 8))(*(int **)(param_1 + 0x28),0);
    (**(code **)(**(int **)(param_1 + 0x28) + 8))(*(int **)(param_1 + 0x28),param_2);
    FUN_400d4b3c(*(undefined4 *)(param_1 + 0x28));
  }
  return;
}


```


## `FUN_400d5130` @ `400d5130` (see decomp_mine/)


## `display_clearDisplay` @ `400d51fc`
```c

void FUN_400d51fc(int param_1)

{
  int iVar1;
  
  iVar1 = *(short *)(param_1 + 10) + 7;
  if (iVar1 < 0) {
    iVar1 = *(short *)(param_1 + 10) + 0xe;
  }
  FUN_40090d70(*(undefined4 *)(param_1 + 0x2c),0,(iVar1 >> 3) * (int)*(short *)(param_1 + 8));
  return;
}


```


## `FUN_400d5220` @ `400d5220` (see decomp_mine/)


## `FUN_400d5490` @ `400d5490` (see decomp_mine/)


## `display_display` @ `400d56b4` (see decomp_mine/)


## `FUN_400d604c` @ `400d604c`
```c

void FUN_400d604c(int *param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = FUN_400d5ffc(param_1,param_3);
  if (iVar1 == 0) {
    FUN_400d5ed4(param_1);
  }
  else {
    piVar2 = param_1;
    if ((*(byte *)((int)param_1 + 0xf) & 0x80) == 0) {
      piVar2 = (int *)*param_1;
    }
    FUN_40090d08(piVar2,param_2,param_3 + 1);
    (*(code *)PTR_FUN_400d0370)(param_1,param_3);
  }
  return;
}


```


## `FUN_400d6084` @ `400d6084`
```c

void FUN_400d6084(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  
  FUN_400d5eb4(param_1);
  if (param_2 != 0) {
    uVar1 = FUN_400912e8(param_2);
    FUN_400d604c(param_1,param_2,uVar1);
  }
  return;
}


```


## `FUN_400d60a0` @ `400d60a0`
```c

int FUN_400d60a0(uint *param_1,uint param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint *puVar4;
  
  if (param_2 != 0) {
    if (param_3 == 0) {
      return 1;
    }
    iVar1 = (*(code *)PTR_FUN_400d0374)(param_1);
    iVar2 = FUN_400d5ffc(param_1,iVar1 + param_3);
    if (iVar2 != 0) {
      puVar4 = param_1;
      if ((*(byte *)((int)param_1 + 0xf) & 0x80) == 0) {
        puVar4 = (uint *)*param_1;
      }
      iVar3 = (*(code *)PTR_FUN_400d0374)(param_1);
      if ((param_2 < puVar4) || ((uint)((int)puVar4 + iVar3) <= param_2)) {
        FUN_40090c10((int)puVar4 + iVar3,param_2,param_3 + 1);
      }
      else {
        FUN_40090d08();
      }
      (*(code *)PTR_FUN_400d0370)(param_1,iVar1 + param_3);
      return iVar2;
    }
  }
  return 0;
}


```


## `FUN_400d6100` @ `400d6100`
```c

undefined4 FUN_400d6100(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (param_2 != 0) {
    uVar1 = FUN_400912e8(param_2);
    uVar1 = FUN_400d60a0(param_1,param_2,uVar1);
  }
  return uVar1;
}


```


## `FUN_400d611c` @ `400d611c`
```c

undefined4 FUN_400d611c(undefined4 param_1,byte param_2)

{
  undefined4 uVar1;
  ushort auStack_22 [17];
  
  auStack_22[0] = (ushort)param_2;
  uVar1 = FUN_400d60a0(param_1,auStack_22,1);
  return uVar1;
}


```


## `FUN_400d6134` @ `400d6134`
```c

void FUN_400d6134(void)

{
  FUN_400d6084(DAT_400d037c,PTR_DAT_400d0378);
  return;
}


```


## `FUN_400d6144` @ `400d6144`
```c

void FUN_400d6144(void)

{
  FUN_400d5ed4(DAT_400d037c);
  return;
}


```


## `FUN_400d6150` @ `400d6150`
```c

bool FUN_400d6150(void)

{
  int iVar1;
  
  iVar1 = FUN_400ff0e4();
  if (iVar1 == 0) {
    return true;
  }
  iVar1 = FUN_400ff0e4();
  if (iVar1 == 2) {
    iVar1 = FUN_400ff094();
    if (iVar1 != 0) {
      return false;
    }
    do {
      iVar1 = FUN_400ff0e4();
    } while (iVar1 == 2);
  }
  iVar1 = FUN_400ff0e4();
  if ((iVar1 == 1) && (iVar1 = FUN_400ff078(), iVar1 == 0)) {
    FUN_40095724(1);
    iVar1 = FUN_400ff0e4();
    return iVar1 == 0;
  }
  return false;
}


```


## `pinMode` @ `400d6198`
```c

void FUN_400d6198(uint param_1,uint param_2)

{
  uint uVar1;
  undefined8 uStack_38;
  uint uStack_30;
  uint uStack_2c;
  undefined4 uStack_28;
  uint uStack_24;
  
  param_1 = param_1 & 0xff;
  uVar1 = (*DAT_400d0394)(DAT_400d0380,DAT_400d0384,param_1);
  if ((uVar1 & 1) != 0) {
    uStack_38 = (*DAT_400d0398)(DAT_400d0388,DAT_400d038c,param_1);
    uStack_30 = 0;
    uStack_2c = 0;
    uStack_28 = 0;
    memw();
    uStack_24 = *(uint *)(DAT_400d0390 + (param_1 + 0x20) * 4 + 8) >> 7 & 7;
    if ((param_2 & 0xff) < 0x20) {
      uStack_30 = param_2 & 3;
      if ((param_2 & 0x10) != 0) {
        uStack_30 = uStack_30 | 4;
      }
      uStack_2c = (uint)((param_2 & 4) != 0);
      if ((param_2 & 8) != 0) {
        uStack_28 = 1;
      }
    }
    FUN_400d862c(&uStack_38);
  }
  return;
}


```


## `digitalWrite` @ `400d6214`
```c

void gpio_write_or_mode(undefined1 param_1,undefined1 param_2)

{
  FUN_400d83d0(param_1,param_2);
  return;
}


```


## `digitalRead` @ `400d6224`
```c

undefined4 FUN_400d6224(undefined1 param_1)

{
  undefined4 uVar1;
  
  uVar1 = FUN_400d84b4(param_1);
  return uVar1;
}


```


## `FUN_400d6234` @ `400d6234`
```c

void FUN_400d6234(char param_1,undefined4 param_2)

{
  undefined8 uStack_38;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  
  uStack_38 = (*DAT_400d0398)(DAT_400d0388,DAT_400d038c,(int)param_1);
  uStack_2c = 1;
  uStack_28 = 0;
  uStack_24 = 0;
  uStack_30 = param_2;
  FUN_400d862c(&uStack_38);
  return;
}


```


## `FUN_400d6260` @ `400d6260` (see decomp_mine/)


## `FUN_400d636c` @ `400d636c`
```c

undefined4 FUN_400d636c(uint param_1)

{
  undefined4 uVar1;
  undefined *puVar2;
  
  uVar1 = 0x102;
  if ((param_1 & 0xff) < 2) {
    puVar2 = PTR_DAT_400d03b4 + (param_1 & 0xff) * 0x30;
    uVar1 = 0x101;
    if (*(int *)(puVar2 + 0x2c) != 0) {
      FUN_40094190(*(int *)(puVar2 + 0x2c),0xffffffff);
      FUN_400d6260(puVar2);
      uVar1 = 0;
      if (*(int *)(puVar2 + 0x2c) != 0) {
        FUN_40093c38(*(int *)(puVar2 + 0x2c),0,0,0);
        uVar1 = 0;
      }
    }
  }
  return uVar1;
}


```


## `FUN_400d63ac` @ `400d63ac`
```c

undefined1 FUN_400d63ac(uint param_1)

{
  undefined1 uVar1;
  
  uVar1 = 0;
  if ((param_1 & 0xff) < 2) {
    memw();
    uVar1 = *(undefined1 *)(DAT_400d03b8 + (param_1 & 0xff) * 0xc);
  }
  return uVar1;
}


```


## `FUN_400d63d0` @ `400d63d0` (see decomp_mine/)


## `FUN_400d64c8` @ `400d64c8`
```c

int FUN_400d64c8(uint param_1)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  
  iVar1 = DAT_400d03b8;
  param_1 = param_1 & 0xff;
  iVar2 = 0x102;
  if (param_1 < 2) {
    pcVar3 = (char *)(DAT_400d03b8 + param_1 * 0xc);
    memw();
    if (*(int *)(pcVar3 + 8) != 0) {
      memw();
      iVar2 = FUN_40094190(*(undefined4 *)(pcVar3 + 8),0xffffffff);
      if (iVar2 == 1) {
        memw();
        iVar2 = -1;
        if ((*pcVar3 != '\0') && (iVar2 = FUN_400d89f4(param_1), iVar2 == 0)) {
          memw();
          *pcVar3 = '\0';
        }
        memw();
        FUN_40093c38(*(undefined4 *)(iVar1 + param_1 * 0xc + 8),0,0);
        return iVar2;
      }
    }
    iVar2 = -1;
  }
  return iVar2;
}


```


## `FUN_400d6534` @ `400d6534` (see decomp_mine/)


## `FUN_400d663c` @ `400d663c` (see decomp_mine/)


## `FUN_400d66dc` @ `400d66dc`
```c

void FUN_400d66dc(void)

{
  FUN_400932f8();
  return;
}


```


## `FUN_400d66e4` @ `400d66e4`
```c

undefined4
FUN_400d66e4(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,uint param_7)

{
  undefined4 uVar1;
  
  if (1 < param_7) {
    param_7 = DAT_400d03a0;
  }
  uVar1 = FUN_400949f4(param_1,param_2,param_3,param_4,param_5,param_6,param_7);
  return uVar1;
}


```


## `millis` @ `400d670c`
```c

undefined4 FUN_400d670c(void)

{
  undefined4 uVar1;
  undefined8 uVar2;
  
  uVar2 = FUN_40084928();
  uVar1 = (*DAT_400d03d4)((int)uVar2,(int)((ulonglong)uVar2 >> 0x20),DAT_400d03d0,DAT_400d038c);
  return uVar1;
}


```


## `delay_ms` @ `400d6724`
```c

void delay_ms(undefined4 param_1)

{
  FUN_40095724(param_1);
  return;
}


```


## `delayMicroseconds` @ `400d6730`
```c

/* WARNING: Removing unreachable block (ram,0x400d676d) */
/* WARNING: Removing unreachable block (ram,0x400d674e) */
/* WARNING: Removing unreachable block (ram,0x400d675a) */

void FUN_400d6730(uint param_1)

{
  ulonglong uVar1;
  ulonglong uVar2;
  
  uVar1 = FUN_40084928();
  if (param_1 != 0) {
    if (uVar1 + param_1 < uVar1) {
      do {
        uVar2 = FUN_40084928();
      } while (uVar1 + param_1 < uVar2);
    }
    do {
      uVar2 = FUN_40084928();
    } while (uVar2 < uVar1 + param_1);
  }
  return;
}


```


## `FUN_400d677c` @ `400d677c`
```c

void FUN_400d677c(void)

{
  int iVar1;
  undefined4 uVar2;
  int aiStack_24 [9];
  
  iVar1 = (*(code *)PTR_FUN_400d03e4)();
  if (iVar1 == 0) {
    uVar2 = FUN_400dc33c();
    iVar1 = FUN_400dc56c(uVar2,aiStack_24);
    if ((iVar1 == 0) && (aiStack_24[0] == 1)) {
      iVar1 = (*(code *)PTR_FUN_400d03e8)();
      if (iVar1 == 0) {
        FUN_400dc560();
      }
      else {
        FUN_400dc554();
      }
    }
  }
  FUN_400d7b0c(0xf0);
  (*(code *)PTR_FUN_400d03ec)(PTR_DAT_400d03d8,1);
  iVar1 = FUN_400dd5f0();
  if ((((iVar1 + DAT_400d03dc == 0) || (iVar1 + DAT_400d03e0 == 0)) &&
      (iVar1 = FUN_400dd0e8(1,2,0), iVar1 != 0)) &&
     (iVar1 = FUN_400dd1cc(iVar1,0,*(undefined4 *)(iVar1 + 0x10)), iVar1 == 0)) {
    FUN_400dd5f0();
  }
  iVar1 = (*(code *)PTR_FUN_400d03f0)();
  if (iVar1 == 0) {
    FUN_400fefa0(3);
  }
  (*(code *)PTR_FUN_400d03f4)();
  (*(code *)PTR_FUN_400d03f8)();
  return;
}


```


## Call graph edges (recovered)

### radioTask @ 400d236c
- 40095724 FUN_40095724
- 400d30d8 nrf_setChannel
- 400d3180 nrf_startListening_or_openPipe
- 400d31d8 nrf_powerDown
- 400d31fc nrf_powerUp
- 400d32c4 nrf_stopListening
- 400d32f4 nrf_setPALevel
- 400d3328 nrf_setDataRate
- 400d3448 nrf_begin
- 400d3460 nrf_setCRCLength
- 400d34b0 nrf_setRetries
- 400d34d8 nrf_startConstCarrier
- 400d3590 nrf_stopConstCarrier
- 400d35d0 spi_setBus
- 400d35fc spi_setPins
- 400d36e4 FUN_400d36e4
- 400d5d1c Serial_println_empty
- 400d5d30 Serial_print
- 400d5e80 randomChannel
- 400d6724 delay_ms
- 4014edb8 FUN_4014edb8
### FUN_400d2714 @ 400d2714
- 400949f4 FUN_400949f4
- 400d2d68 FUN_400d2d68
- 400d2dac FUN_400d2dac
- 400d3e5c FUN_400d3e5c
- 400d5ac4 FUN_400d5ac4
- 400d5d1c Serial_println_empty
- 400d5d30 Serial_print
- 400d6150 FUN_400d6150
- 400d6198 pinMode
- 400d6724 delay_ms
- 4015e3c0 FUN_4015e3c0
### FUN_400d2bfc @ 400d2bfc
- 400d2844 FUN_400d2844
- 400d28d8 enterState_BT
- 400d2920 enterState_BLE
- 400d2968 enterState_WiFi
- 400d29b0 enterState_RC
- 400d2a24 FUN_400d2a24
- 400d380c FUN_400d380c
- 400d6224 digitalRead
- 400d670c millis
- 4015e3c8 FUN_4015e3c8
### FUN_400d2d68 @ 400d2d68
- 400d493c FUN_400d493c
- 400d51fc display_clearDisplay
- 400d5220 FUN_400d5220
- 400d56b4 display_display
- 400d5d30 Serial_print
### FUN_400d2dac @ 400d2dac
- 40082e5c FUN_40082e5c
- 400910b8 FUN_400910b8
- 400d4fd8 FUN_400d4fd8
- 400d51fc display_clearDisplay
- 400d56b4 display_display
- 400d5eec FUN_400d5eec
- 400d6084 FUN_400d6084
- 4015e924 FUN_4015e924
- 4015ebe4 FUN_4015ebe4
### FUN_400d29f8 @ 400d29f8
- 400d30a8 FUN_400d30a8
- 400d37d8 FUN_400d37d8
### nrf_begin_chipInit @ 400d337c
- 400d2fcc nrf_readRegister
- 400d3034 nrf_writeRegister
- 400d3060 nrf_flushRx
- 400d3078 nrf_flushTx
- 400d30d8 nrf_setChannel
- 400d30f0 nrf_setPayloadSize
- 400d31fc nrf_powerUp
- 400d3248 nrf_setAddressWidth
- 400d327c FUN_400d327c
- 400d3328 nrf_setDataRate
- 400d6724 delay_ms

## Data xrefs sample

### radioH 3ffc3b88
- (no direct xrefs; may be only via DAT_* pool)
### radioV 3ffc3b60
- (no direct xrefs; may be only via DAT_* pool)
### g_state 3ffbdb7c
- 400d284d READ
- 400d2854 WRITE
- 400d2859 READ
- 400d2863 WRITE
- 400d2c49 READ
- 400d2c89 READ
- 400d2c98 WRITE
- 400d2cdb WRITE
- 400d2cf5 READ
- 400d2666 READ
- 400d0080 DATA
### chV 3ffbdb70
- 400d2655 READ
- 400d2531 READ
- 400d0068 DATA
### chH 3ffbdb74
- 400d2645 READ
- 400d2481 READ
- 400d0040 DATA

Done functions decompiled: 89
