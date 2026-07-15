# Additional decompilation & call graph

## Callers of 0x400D28D8
- from 400d2d18 in FUN_400d2bfc @ 400d2bfc type=UNCONDITIONAL_CALL
- from 400d2d51 in FUN_400d2bfc @ 400d2bfc type=UNCONDITIONAL_CALL

## Callers of 0x400D2920
- from 400d2d21 in FUN_400d2bfc @ 400d2bfc type=UNCONDITIONAL_CALL
- from 400d2d58 in FUN_400d2bfc @ 400d2bfc type=UNCONDITIONAL_CALL

## Callers of 0x400D2968
- from 400d2d28 in FUN_400d2bfc @ 400d2bfc type=UNCONDITIONAL_CALL
- from 400d2d61 in FUN_400d2bfc @ 400d2bfc type=UNCONDITIONAL_CALL

## Callers of 0x400D29B0
- from 400d2d12 in FUN_400d2bfc @ 400d2bfc type=UNCONDITIONAL_CALL
- from 400d2d42 in FUN_400d2bfc @ 400d2bfc type=UNCONDITIONAL_CALL

## Callers of 0x400D2A24
- from 400d2d48 in FUN_400d2bfc @ 400d2bfc type=UNCONDITIONAL_CALL

## Callers of 0x400D236C
- from 400d00f0 in ? type=DATA

## Callers of 0x400D2DAC
- from 400d293f in FUN_400d2920 @ 400d2920 type=UNCONDITIONAL_CALL
- from 400d2987 in FUN_400d2968 @ 400d2968 type=UNCONDITIONAL_CALL
- from 400d29cf in FUN_400d29b0 @ 400d29b0 type=UNCONDITIONAL_CALL
- from 400d28f7 in FUN_400d28d8 @ 400d28d8 type=UNCONDITIONAL_CALL
- from 400d275e in FUN_400d2714 @ 400d2714 type=UNCONDITIONAL_CALL

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
    uVar2 = FUN_400d337c(param_1);
  }
  return uVar2;
}

```

## `FUN_400d5d08` @ `400d5d08`
```c

undefined4 FUN_400d5d08(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = FUN_400d5ce8(param_1,param_2);
  return uVar1;
}

```

## `FUN_400d32c4` @ `400d32c4`
```c

void FUN_400d32c4(int param_1,char param_2)

{
  if (param_2 == '\0') {
    FUN_400d3034(param_1,1);
    if (*(char *)(param_1 + 0x1b) != '\0') {
      FUN_400d32a0(param_1);
    }
  }
  else {
    FUN_400d3034(param_1,1,0x3f);
  }
  return;
}

```

## `randomChannel` @ `400d5e80`
```c

uint randomChannel(uint param_1)

{
  uint uVar1;
  
  uVar1 = 0;
  if (param_1 != 0) {
    if ((int)param_1 < 0) {
      uVar1 = FUN_400d5e70(0,-param_1);
    }
    else {
      if (*PTR_DAT_400d036c == '\0') {
        uVar1 = FUN_40090e08();
      }
      else {
        uVar1 = FUN_400841ac();
      }
      uVar1 = uVar1 % param_1;
    }
  }
  return uVar1;
}

```

## `FUN_400d3180` @ `400d3180`
```c

void FUN_400d3180(int param_1)

{
  byte bVar1;
  
  FUN_400d2f4c(param_1,0);
  FUN_400d6730(*(undefined4 *)(param_1 + 0x20));
  if (*(char *)(param_1 + 0x1b) != '\0') {
    FUN_400d3078(param_1);
  }
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfe;
  FUN_400d3034(param_1,0);
  FUN_400d2ff8(param_1,10,param_1 + 0x13,*(undefined1 *)(param_1 + 0x1c));
  bVar1 = FUN_400d2fcc(param_1,2);
  FUN_400d3034(param_1,2,bVar1 | 1);
  return;
}

```

## `Serial_println_empty` @ `400d5d1c`
```c

undefined4 Serial_println_empty(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = FUN_400d5ce8(param_1,PTR_s__3f406b34_0x23_400d0364);
  return uVar1;
}

```

## `enterState_BT` @ `400d28d8`
```c

void enterState_BT(void)

{
  int *piVar1;
  undefined *puVar2;
  undefined4 uVar3;
  
  piVar1 = DAT_400d0108;
  if (*DAT_400d0108 != 1) {
    FUN_400d5d30(DAT_400d0028,table_state_strings);
    puVar2 = PTR_str_bitmap1_400d0110;
    *piVar1 = 1;
    FUN_400d2dac(puVar2,0);
    uVar3 = FUN_400d670c();
    *DAT_400d00fc = uVar3;
    *DAT_400d0100 = 0;
    *PTR_DAT_400d00f8 = 0;
    FUN_400d6214(0x1b);
    *(undefined4 *)PTR_DAT_400d0104 = 1;
  }
  FUN_400d2868();
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
  FUN_400d3034(param_1,5,param_2);
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
  FUN_400d3180(param_1);
  bVar2 = FUN_400d2fcc(param_1,6);
  FUN_400d3034(param_1,6,bVar2 | 0x90);
  if (*(char *)(param_1 + 0x19) != '\0') {
    FUN_400d32c4(param_1,0);
    FUN_400d3034(param_1,4,0);
    local_44[0] = 0xff;
    FUN_400d2ff8(param_1,0x10,local_44,5);
    FUN_400d3078(param_1);
    FUN_400d2ff8(param_1,0xa0,local_44,0x20);
    FUN_400d3494(param_1);
  }
  FUN_400d32f4(param_1,param_2,1);
  nrf_setChannel(param_1,param_3);
  FUN_400d2f4c(param_1,1);
  if (*(char *)(param_1 + 0x19) != '\0') {
    FUN_400d6724(1);
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

## `FUN_400d31d8` @ `400d31d8`
```c

void FUN_400d31d8(int param_1)

{
  FUN_400d2f4c(param_1,0);
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfd;
  FUN_400d3034(param_1,0);
  return;
}

```

## `FUN_400d4fd8` @ `400d4fd8`
```c

void FUN_400d4fd8(undefined4 param_1,undefined1 param_2)

{
  (*(code *)PTR_FUN_400d02ec)(param_1,param_2,param_2);
  return;
}

```

## `FUN_400d2714` @ `400d2714`
```c

void FUN_400d2714(void)

{
  undefined4 uVar1;
  undefined *puVar2;
  
  FUN_400d3e5c(0);
  FUN_400d6150();
  uVar1 = DAT_400d0028;
  FUN_400d5ac4(DAT_400d0028,DAT_400d0094,DAT_400d0090,0xffffffff,0xffffffff,0,DAT_400d0098,0x70);
  (*(code *)PTR_FUN_400d00f4)(DAT_400d009c,0x32);
  FUN_400d6198(0x1b,3);
  FUN_400d2d68();
  FUN_400d6198(0,5);
  FUN_400d2dac(PTR_str_bitmapboot_400d00a0,1);
  FUN_400d6724(2000);
  puVar2 = PTR_s__________________________________400d00a4;
  FUN_400d5d30(uVar1,PTR_s__________________________________400d00a4);
  Serial_println_empty(uVar1);
  FUN_400d5d30(uVar1,PTR_DAT_400d00a8);
  FUN_400d5d30(uVar1,PTR_DAT_400d00ac);
  FUN_400d5d30(uVar1,PTR_DAT_400d00b0);
  FUN_400d5d30(uVar1,PTR_DAT_400d00b4);
  FUN_400d5d30(uVar1,PTR_DAT_400d00b8);
  Serial_println_empty(uVar1);
  FUN_400d5d30(uVar1,puVar2);
  Serial_println_empty(uVar1);
  FUN_400d5d30(uVar1,PTR_str_Firmware_Banner_400d00bc);
  Serial_println_empty(uVar1);
  FUN_400d5d30(uVar1,PTR_DAT_400d00c0);
  FUN_400d5d30(uVar1,PTR_DAT_400d00c4);
  FUN_400d5d30(uVar1,PTR_DAT_400d00c8);
  FUN_400d5d30(uVar1,PTR_DAT_400d00cc);
  FUN_400d5d30(uVar1,PTR_DAT_400d00d0);
  FUN_400d5d30(uVar1,PTR_DAT_400d00d4);
  Serial_println_empty(uVar1);
  FUN_400d5d30(uVar1,puVar2);
  Serial_println_empty(uVar1);
  FUN_400d5d30(uVar1,PTR_str_Educational_400d00d8);
  Serial_println_empty(uVar1);
  FUN_400d5d30(uVar1,PTR_str_GitHub_URL_400d00dc);
  Serial_println_empty(uVar1);
  FUN_400d5d30(uVar1,PTR_str_Disclaimer_400d00e0);
  Serial_println_empty(uVar1);
  FUN_400d5d30(uVar1,puVar2);
  FUN_400949f4(ptr_radioTask_fn,ptr_RadioTask_name,DAT_400d00e8,0,1,DAT_400d00e4,0);
  return;
}

```

## `gpio_write_or_mode` @ `400d6214`
```c

void gpio_write_or_mode(undefined1 param_1,undefined1 param_2)

{
  FUN_400d83d0(param_1,param_2);
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

## `FUN_400d3590` @ `400d3590`
```c

void FUN_400d3590(int param_1)

{
  uint uVar1;
  
  FUN_400d31d8(param_1);
  uVar1 = FUN_400d2fcc(param_1,6);
  FUN_400d3034(param_1,6,uVar1 & 0x6f);
  FUN_400d2f4c(param_1,0);
  FUN_400d3078(param_1);
  if (*(char *)(param_1 + 0x19) != '\0') {
    FUN_400d2ff8(param_1,0x10,param_1 + 0x13,*(undefined1 *)(param_1 + 0x1c));
  }
  return;
}

```

## `enterState_WiFi` @ `400d2968`
```c

void enterState_WiFi(void)

{
  int *piVar1;
  undefined *puVar2;
  undefined4 uVar3;
  
  piVar1 = DAT_400d0108;
  if (*DAT_400d0108 != 3) {
    FUN_400d5d30(DAT_400d0028,PTR_str_State3_WiFi_400d011c);
    puVar2 = PTR_str_bitmap3_400d0120;
    *piVar1 = 3;
    FUN_400d2dac(puVar2,0);
    uVar3 = FUN_400d670c();
    *DAT_400d00fc = uVar3;
    *DAT_400d0100 = 0;
    *PTR_DAT_400d00f8 = 0;
    gpio_write_or_mode(0x1b);
    *(undefined4 *)PTR_DAT_400d0104 = 3;
  }
  FUN_400d2868();
  return;
}

```

## `statusLedBlink` @ `400d2868`
```c

void statusLedBlink(void)

{
  byte bVar1;
  undefined *puVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  
  iVar4 = FUN_400d670c();
  puVar2 = PTR_DAT_400d00f8;
  bVar1 = *PTR_DAT_400d00f8;
  if (bVar1 == 0) {
    if ((uint)(iVar4 - *DAT_400d00fc) < 0x96) {
      return;
    }
  }
  else {
    uVar6 = 0x96;
    if (*DAT_400d0100 == *(int *)PTR_DAT_400d0104) {
      uVar6 = 1000;
    }
    if ((uint)(iVar4 - *DAT_400d00fc) < uVar6) {
      return;
    }
  }
  *DAT_400d00fc = iVar4;
  *puVar2 = bVar1 ^ 1;
  gpio_write_or_mode(0x1b);
  piVar3 = DAT_400d0100;
  if ((*puVar2 != '\0') &&
     (iVar5 = *DAT_400d0100, iVar4 = *(int *)PTR_DAT_400d0104, *DAT_400d0100 = iVar5 + 1,
     iVar4 < iVar5 + 1)) {
    *piVar3 = 1;
  }
  return;
}

```

## `FUN_400d3328` @ `400d3328`
```c

bool FUN_400d3328(int param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = FUN_400d2fcc(param_1,6);
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
  FUN_400d3034(param_1,6,uVar2);
  uVar1 = FUN_400d2fcc(param_1,6);
  return uVar2 == uVar1;
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

## `delay_ms` @ `400d6724`
```c

void delay_ms(undefined4 param_1)

{
  FUN_40095724(param_1);
  return;
}

```

## `enterState_BLE` @ `400d2920`
```c

void enterState_BLE(void)

{
  int *piVar1;
  undefined *puVar2;
  undefined4 uVar3;
  
  piVar1 = DAT_400d0108;
  if (*DAT_400d0108 != 2) {
    FUN_400d5d30(DAT_400d0028,PTR_str_State2_BLE_400d0114);
    puVar2 = PTR_str_bitmap2_400d0118;
    *piVar1 = 2;
    FUN_400d2dac(puVar2,0);
    uVar3 = FUN_400d670c();
    *DAT_400d00fc = uVar3;
    *DAT_400d0100 = 0;
    *PTR_DAT_400d00f8 = 0;
    gpio_write_or_mode(0x1b);
    *(undefined4 *)PTR_DAT_400d0104 = 2;
  }
  statusLedBlink();
  return;
}

```

## `FUN_400d3460` @ `400d3460`
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
  FUN_400d3034(param_1,0,*(undefined1 *)(param_1 + 0x18));
  return;
}

```

## `nrf_isChipConnected` @ `400d3120`
```c

bool nrf_isChipConnected(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_400d2fcc(param_1,3);
  return *(byte *)(param_1 + 0x1c) - 2 == iVar1;
}

```

## `FUN_400d2bfc` @ `400d2bfc`
```c

void FUN_400d2bfc(void)

{
  char *pcVar1;
  undefined *puVar2;
  undefined4 uVar3;
  int *piVar4;
  char *pcVar5;
  char *pcVar6;
  int iVar7;
  undefined4 uVar8;
  
  uVar3 = DAT_400d009c;
  FUN_400d380c(DAT_400d009c);
  iVar7 = FUN_400d6224(0);
  pcVar5 = DAT_400d017c;
  piVar4 = DAT_400d0178;
  puVar2 = PTR_DAT_400d0080;
  pcVar1 = DAT_400d007c;
  if (iVar7 == 0) {
    if (*DAT_400d0178 == 0) {
      iVar7 = FUN_400d670c();
      *piVar4 = iVar7;
    }
    else {
      memw();
      if (((*DAT_400d007c == '\0') && (*DAT_400d017c == '\0')) &&
         (iVar7 = FUN_400d670c(), 499 < (uint)(iVar7 - *piVar4))) {
        memw();
        memw();
        *(undefined4 *)PTR_DAT_400d0180 = *(undefined4 *)puVar2;
        memw();
        *(undefined4 *)puVar2 = 0;
        memw();
        *pcVar1 = '\x01';
        *pcVar5 = '\x01';
      }
    }
  }
  else if (*DAT_400d0178 != 0) {
    iVar7 = FUN_400d670c();
    pcVar5 = DAT_400d017c;
    memw();
    if (((uint)(iVar7 - *piVar4) < 500) && (*pcVar1 != '\0')) {
      memw();
      uVar8 = *(undefined4 *)PTR_DAT_400d0180;
      *DAT_400d017c = '\0';
      memw();
      *(undefined4 *)puVar2 = uVar8;
      pcVar6 = DAT_400d0184;
      memw();
      *pcVar1 = '\0';
      *pcVar6 = '\x01';
      *DAT_400d0108 = 0;
      memw();
      iVar7 = *(int *)puVar2;
      if (iVar7 == 2) {
        enterState_BLE();
      }
      else if (iVar7 < 3) {
        if (iVar7 == 1) {
          enterState_BT();
        }
      }
      else if (iVar7 == 3) {
        enterState_WiFi();
      }
      else if (iVar7 == 4) {
        FUN_400d29b0();
      }
    }
    *piVar4 = 0;
    *pcVar5 = '\0';
  }
  memw();
  if ((*pcVar1 == '\0') && (iVar7 = (*(code *)PTR_FUN_400d0188)(uVar3), iVar7 != 0)) {
    if (*DAT_400d0184 == '\0') {
      FUN_400d2844();
    }
    else {
      *DAT_400d0184 = '\0';
    }
  }
  memw();
  iVar7 = *(int *)puVar2;
  if (iVar7 == 2) {
    enterState_BLE();
  }
  else if (iVar7 < 3) {
    if (iVar7 == 0) {
      FUN_400d2a24();
    }
    else if (iVar7 == 1) {
      enterState_BT();
    }
  }
  else if (iVar7 == 3) {
    enterState_WiFi();
  }
// truncated
```

## `spi_setPins` @ `400d35fc`
```c

void spi_setPins(char *param_1,byte param_2,byte param_3,byte param_4,byte param_5)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  char cVar4;
  
  if (*(int *)(param_1 + 4) == 0) {
    if (*(int *)(param_1 + 0x10) == 0) {
      uVar2 = FUN_400d7038(*(undefined4 *)(param_1 + 0x14));
      *(undefined4 *)(param_1 + 0x10) = uVar2;
    }
    iVar3 = FUN_400d6d08(*param_1,*(undefined4 *)(param_1 + 0x10),0,1);
    *(int *)(param_1 + 4) = iVar3;
    if (iVar3 != 0) {
      if ((param_4 & param_5 & param_3 & param_2) == 0xff) {
        cVar1 = *param_1;
        cVar4 = '\x12';
        if (cVar1 != '\x03') {
          cVar4 = '\x0e';
        }
        param_1[9] = cVar4;
        cVar4 = '\x13';
        if (cVar1 != '\x03') {
          cVar4 = '\f';
        }
        param_1[10] = cVar4;
        cVar4 = '\x17';
        if (cVar1 != '\x03') {
          cVar4 = '\r';
        }
        param_1[0xb] = cVar4;
        cVar4 = '\x0f';
        if (cVar1 == '\x03') {
          cVar4 = '\x05';
        }
        param_1[0xc] = cVar4;
      }
      else {
        param_1[9] = param_2;
        param_1[10] = param_3;
        param_1[0xb] = param_4;
        param_1[0xc] = param_5;
      }
      FUN_400d680c(iVar3,(int)param_1[9]);
      FUN_400d6860(*(undefined4 *)(param_1 + 4),(int)param_1[10]);
      FUN_400d68cc(*(undefined4 *)(param_1 + 4),(int)param_1[0xb]);
    }
  }
  return;
}

```

## `FUN_400d31fc` @ `400d31fc`
```c

void FUN_400d31fc(int param_1)

{
  if ((*(byte *)(param_1 + 0x18) & 2) == 0) {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) | 2;
    FUN_400d3034(param_1);
    FUN_400d6730(DAT_400d01dc);
  }
  return;
}

```

## `FUN_400d51fc` @ `400d51fc`
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

## `FUN_400d32f4` @ `400d32f4`
```c

void FUN_400d32f4(undefined4 param_1,byte param_2,char param_3)

{
  byte bVar1;
  
  bVar1 = FUN_400d2fcc(param_1,6);
  FUN_400d3034(param_1,6,
               bVar1 & 0xf8 | param_3 + ((param_2 < 3) * param_2 + (param_2 >= 3) * '\x03') * '\x02'
              );
  return;
}

```

## `FUN_400d56b4` @ `400d56b4`
```c

void FUN_400d56b4(int param_1)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  byte *pbVar4;
  ushort uVar5;
  uint uVar6;
  
  if (*(int *)(param_1 + 0x28) == 0) {
    if (*(int *)(param_1 + 0x24) != 0) {
      FUN_400d3730(*(int *)(param_1 + 0x24),*(undefined4 *)(param_1 + 0x44),
                   *(undefined4 *)(param_1 + 0x48));
    }
    gpio_write_or_mode(*(undefined1 *)(param_1 + 0x36),0);
  }
  else {
    FUN_400d4a4c(*(int *)(param_1 + 0x28),*(undefined4 *)(param_1 + 0x38));
  }
  FUN_400d5130(param_1,PTR_DAT_400d0324,5);
  FUN_400d505c(param_1,*(char *)(param_1 + 8) + -1);
  iVar2 = *(short *)(param_1 + 10) + 7;
  if (iVar2 < 0) {
    iVar2 = *(short *)(param_1 + 10) + 0xe;
  }
  pbVar4 = *(byte **)(param_1 + 0x2c);
  uVar3 = (uint)*(ushort *)(param_1 + 8) * (iVar2 >> 3 & 0xffffU) & 0xffff;
  if (*(int *)(param_1 + 0x28) == 0) {
    gpio_write_or_mode(*(undefined1 *)(param_1 + 0x35),1);
    while (uVar3 = uVar3 - 1 & 0xffff, uVar3 != DAT_400d0328) {
      bVar1 = *pbVar4;
      if (*(int *)(param_1 + 0x24) == 0) {
        iVar2 = 8;
        uVar6 = 0x80;
        do {
          gpio_write_or_mode(*(undefined1 *)(param_1 + 0x33),bVar1 & uVar6);
          gpio_write_or_mode(*(undefined1 *)(param_1 + 0x34),1);
          gpio_write_or_mode(*(undefined1 *)(param_1 + 0x34),0);
          iVar2 = iVar2 + -1;
          uVar6 = uVar6 >> 1;
        } while (iVar2 != 0);
      }
      else {
        FUN_400d379c(*(int *)(param_1 + 0x24),(uint)bVar1);
      }
      pbVar4 = pbVar4 + 1;
    }
  }
  else {
    FUN_400d4b2c(*(int *)(param_1 + 0x28),(int)*(char *)(param_1 + 0x30));
    (**(code **)(**(int **)(param_1 + 0x28) + 8))(*(int **)(param_1 + 0x28),0x40);
    uVar6 = DAT_400d0328;
    uVar5 = 1;
    while( true ) {
      uVar3 = uVar3 - 1 & 0xffff;
      if (uVar3 == uVar6) break;
      if (0x7f < uVar5) {
        FUN_400d4b3c(*(undefined4 *)(param_1 + 0x28));
        FUN_400d4b2c(*(undefined4 *)(param_1 + 0x28),(int)*(char *)(param_1 + 0x30));
        (**(code **)(**(int **)(param_1 + 0x28) + 8))(*(int **)(param_1 + 0x28),0x40);
        uVar5 = 1;
      }
      uVar5 = uVar5 + 1;
      (**(code **)(**(int **)(param_1 + 0x28) + 8))(*(int **)(param_1 + 0x28),*pbVar4);
      pbVar4 = pbVar4 + 1;
    }
    FUN_400d4b3c(*(undefined4 *)(param_1 + 0x28));
  }
  if (*(int *)(param_1 + 0x28) == 0) {
    gpio_write_or_mode(*(undefined1 *)(param_1 + 0x36),1);
    if (*(int *)(param_1 + 0x24) != 0) {
      FUN_400d3778();
    }
  }
  else {
    FUN_400d4a4c(*(int *)(param_1 + 0x28),*(undefined4 *)(param_1 + 0x3c));
  }
  return;
}

```

## `enterState_RC` @ `400d29b0`
```c

void enterState_RC(void)

{
  int *piVar1;
  undefined *puVar2;
  undefined4 uVar3;
  
  piVar1 = DAT_400d0108;
  if (*DAT_400d0108 != 4) {
    FUN_400d5d30(DAT_400d0028,PTR_str_State4_RC_400d0124);
    puVar2 = PTR_str_bitmap4_400d0128;
    *piVar1 = 4;
    FUN_400d2dac(puVar2,0);
    uVar3 = FUN_400d670c();
    *DAT_400d00fc = uVar3;
    *DAT_400d0100 = 0;
    *PTR_DAT_400d00f8 = 0;
    gpio_write_or_mode(0x1b);
    *(undefined4 *)PTR_DAT_400d0104 = 4;
  }
  statusLedBlink();
  return;
}

```

## `FUN_400d34b0` @ `400d34b0`
```c

void FUN_400d34b0(undefined4 param_1,byte param_2,byte param_3)

{
  FUN_400d3034(param_1,4,
               ((param_2 < 0xf) * param_2 + (param_2 >= 0xf) * '\x0f') * '\x10' |
               (param_3 < 0xf) * param_3 + (param_3 >= 0xf) * '\x0f');
  return;
}

```

## `Serial_print` @ `400d5d30`
```c

int Serial_print(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_400d5ce8(param_1,param_2);
  iVar2 = Serial_println_empty(param_1);
  return iVar2 + iVar1;
}

```

