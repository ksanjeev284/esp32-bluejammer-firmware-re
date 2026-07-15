# Gap fill decompilation
Targets: 36

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
  delay_ms(2000);
  puVar2 = PTR_s__________________________________400d00a4;
  Serial_print(uVar1,PTR_s__________________________________400d00a4);
  Serial_println_empty(uVar1);
  Serial_print(uVar1,PTR_DAT_400d00a8);
  Serial_print(uVar1,PTR_DAT_400d00ac);
  Serial_print(uVar1,PTR_DAT_400d00b0);
  Serial_print(uVar1,PTR_DAT_400d00b4);
  Serial_print(uVar1,PTR_DAT_400d00b8);
  Serial_println_empty(uVar1);
  Serial_print(uVar1,puVar2);
  Serial_println_empty(uVar1);
  Serial_print(uVar1,PTR_str_Firmware_Banner_400d00bc);
  Serial_println_empty(uVar1);
  Serial_print(uVar1,PTR_DAT_400d00c0);
  Serial_print(uVar1,PTR_DAT_400d00c4);
  Serial_print(uVar1,PTR_DAT_400d00c8);
  Serial_print(uVar1,PTR_DAT_400d00cc);
  Serial_print(uVar1,PTR_DAT_400d00d0);
  Serial_print(uVar1,PTR_DAT_400d00d4);
  Serial_println_empty(uVar1);
  Serial_print(uVar1,puVar2);
  Serial_println_empty(uVar1);
  Serial_print(uVar1,PTR_str_Educational_400d00d8);
  Serial_println_empty(uVar1);
  Serial_print(uVar1,PTR_str_GitHub_URL_400d00dc);
  Serial_println_empty(uVar1);
  Serial_print(uVar1,PTR_str_Disclaimer_400d00e0);
  Serial_println_empty(uVar1);
  Serial_print(uVar1,puVar2);
  FUN_400949f4(ptr_radioTask_fn,ptr_RadioTask_name,DAT_400d00e8,0,1,DAT_400d00e4,0);
  return;
}

```

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

## `FUN_400d3e5c` @ `400d3e5c`
```c

bool FUN_400d3e5c(uint param_1)

{
  bool bVar1;
  bool bVar2;
  char *pcVar3;
  byte *pbVar4;
  uint uVar5;
  int iVar6;
  
  uVar5 = FUN_400d3e38();
  pcVar3 = DAT_400d025c;
  if (uVar5 != param_1) {
    bVar1 = uVar5 == 0;
    bVar2 = param_1 != 0;
    if (bVar1 && bVar2) {
      iVar6 = FUN_400d3ce4(*PTR_DAT_400d0260);
      if (iVar6 == 0) {
        return false;
      }
    }
    else if ((uVar5 != 0 || bVar1 && bVar2) && (param_1 == 0 || bVar1 && bVar2)) {
      if (*DAT_400d025c == '\0') {
        return true;
      }
      *DAT_400d025c = bVar1 && bVar2;
      iVar6 = FUN_40126788();
      pbVar4 = DAT_400d0240;
      if (iVar6 == 0) {
        if (*DAT_400d0240 != 0) {
          iVar6 = FUN_400e9ee0();
          *pbVar4 = iVar6 != 0;
        }
        return (bool)(*pbVar4 ^ 1);
      }
      *pcVar3 = '\x01';
      return bVar1 && bVar2;
    }
    pcVar3 = DAT_400d01f8;
    if ((param_1 & 1) != 0) {
      if (*DAT_400d01f8 == '\0') {
        FUN_400d38a0();
      }
      iVar6 = FUN_400d38e8(0,pcVar3);
      if (iVar6 != 0) {
        return false;
      }
    }
    iVar6 = FUN_401266cc(param_1);
    if ((iVar6 != 0) ||
       ((*DAT_400d0264 != '\0' &&
        ((((param_1 & 1) != 0 && (iVar6 = FUN_40126e14(0,8), iVar6 != 0)) ||
         (((param_1 & 2) != 0 && (iVar6 = FUN_40126e14(1,8), iVar6 != 0)))))))) {
      return false;
    }
    pcVar3 = DAT_400d025c;
    if (*DAT_400d025c == '\0') {
      *DAT_400d025c = '\x01';
      iVar6 = FUN_40126730();
      if (iVar6 == 0) {
        return (bool)*pcVar3;
      }
      *pcVar3 = '\0';
      return false;
    }
  }
  return true;
}

```

## `FUN_400d5ac4` @ `400d5ac4`
```c

void FUN_400d5ac4(int param_1,uint param_2,undefined4 param_3,uint param_4,uint param_5,
                 undefined1 param_6,uint param_7,undefined1 param_8)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 uVar4;
  char cVar5;
  char cVar7;
  uint uVar8;
  char cVar9;
  uint uVar6;
  
  uVar6 = param_4 & 0xff;
  cVar5 = (char)param_4;
  uVar8 = param_5 & 0xff;
  cVar7 = (char)param_5;
  if (2 < *(uint *)(param_1 + 0x10)) {
    return;
  }
  if (*(int *)(param_1 + 0x48) == 0) {
    return;
  }
  do {
    iVar1 = FUN_40094190(*(undefined4 *)(param_1 + 0x48),0xffffffff);
  } while (iVar1 != 1);
  iVar1 = FUN_400d7358(*(undefined4 *)(param_1 + 0x14));
  if (iVar1 == 0) {
    iVar1 = *(int *)(param_1 + 0x10);
    if (iVar1 == 1) {
      if (uVar6 >> 7 != 0) {
        if (uVar8 >> 7 != 0) {
          cVar7 = '\n';
        }
        cVar9 = '\t';
        goto LAB_400d5b1b;
      }
    }
    else if (iVar1 == 2) {
      if (uVar6 >> 7 != 0) {
        if (uVar8 >> 7 != 0) {
          cVar7 = '\x11';
        }
        cVar9 = '\x10';
LAB_400d5b1b:
        if (uVar8 >> 7 != 0) {
          cVar5 = cVar9;
        }
      }
    }
    else if ((iVar1 == 0) && (uVar6 >> 7 != 0)) {
      if (uVar8 >> 7 != 0) {
        cVar7 = '\x01';
      }
      cVar9 = '\x03';
      goto LAB_400d5b1b;
    }
  }
  if (*(int *)(param_1 + 0x14) != 0) {
    FUN_400d59f4(param_1,0);
  }
  uVar6 = param_2;
  if (param_2 == 0) {
    uVar6 = DAT_400d0358;
  }
  uVar2 = FUN_400d7668(*(undefined1 *)(param_1 + 0x10),uVar6,param_3,(int)cVar5,(int)cVar7,
                       *(undefined2 *)(param_1 + 0x18),*(undefined2 *)(param_1 + 0x1c),param_6,
                       param_8);
  *(undefined4 *)(param_1 + 0x14) = uVar2;
  if (param_2 == 0) {
    FUN_400d7878();
    iVar1 = FUN_400d670c();
    while (iVar3 = FUN_400d670c(), (uint)(iVar3 - iVar1) < param_7) {
      iVar3 = FUN_400d78c8(*(undefined4 *)(param_1 + 0x14));
      if (iVar3 != 0) goto LAB_400d5bae;
      FUN_400d66dc();
    }
    iVar3 = 0;
// truncated
```

## `FUN_400d6198` @ `400d6198`
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

## `FUN_400d2844` @ `400d2844`
```c

void FUN_400d2844(void)

{
  undefined *puVar1;
  
  puVar1 = PTR_DAT_400d0080;
  memw();
  memw();
  *(int *)PTR_DAT_400d0080 = *(int *)PTR_DAT_400d0080 + 1;
  memw();
  if (4 < *(int *)puVar1) {
    memw();
    *(undefined4 *)puVar1 = 1;
  }
  return;
}

```

## `FUN_400d337c` @ `400d337c`
```c

bool FUN_400d337c(int param_1)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  
  delay_ms(5);
  FUN_400d3034(param_1,4,0x5f);
  FUN_400d3328(param_1,0);
  iVar2 = FUN_400d2fcc(param_1,0x1d);
  FUN_400d327c(param_1);
  iVar3 = FUN_400d2fcc(param_1,0x1d);
  *(bool *)(param_1 + 0x19) = iVar2 == iVar3;
  if (iVar3 != 0) {
    if (iVar2 == iVar3) {
      FUN_400d327c(param_1);
    }
    FUN_400d3034(param_1,0x1d,0);
  }
  *(undefined1 *)(param_1 + 0x1b) = 0;
  FUN_400d3034(param_1,0x1c,0);
  *(undefined1 *)(param_1 + 0x1d) = 0;
  FUN_400d3034(param_1,1,0x3f);
  FUN_400d3034(param_1,2,3);
  FUN_400d30f0(param_1,0x20);
  FUN_400d3248(param_1,5);
  nrf_setChannel(param_1,0x4c);
  FUN_400d3034(param_1,7,0x70);
  FUN_400d3060(param_1);
  FUN_400d3078(param_1);
  FUN_400d3034(param_1,0,0xc);
  uVar1 = FUN_400d2fcc(param_1,0);
  *(undefined1 *)(param_1 + 0x18) = uVar1;
  FUN_400d31fc(param_1);
  return *(char *)(param_1 + 0x18) == '\x0e';
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
    FUN_400d2f4c(param_1,0);
    FUN_400d2f38(param_1,1);
  }
  return iVar1;
}

```

## `FUN_400d3034` @ `400d3034`
```c

void FUN_400d3034(undefined4 *param_1,byte param_2,undefined1 param_3)

{
  undefined1 uVar1;
  
  FUN_400d2f60(param_1);
  uVar1 = FUN_400d379c(*param_1,param_2 | 0x20);
  *(undefined1 *)(param_1 + 3) = uVar1;
  FUN_400d379c(*param_1,param_3);
  FUN_400d2f7c(param_1);
  return;
}

```

## `FUN_400d2fcc` @ `400d2fcc`
```c

undefined4 FUN_400d2fcc(undefined4 *param_1,undefined1 param_2)

{
  undefined1 uVar1;
  undefined4 uVar2;
  
  FUN_400d2f60(param_1);
  uVar1 = FUN_400d379c(*param_1,param_2);
  *(undefined1 *)(param_1 + 3) = uVar1;
  uVar2 = FUN_400d379c(*param_1,0xff);
  FUN_400d2f7c(param_1);
  return uVar2;
}

```

## `FUN_400d2f4c` @ `400d2f4c`
```c

void FUN_400d2f4c(int param_1,undefined1 param_2)

{
  if (*(char *)(param_1 + 5) != *(char *)(param_1 + 4)) {
    gpio_write_or_mode(*(char *)(param_1 + 4),param_2);
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

## `FUN_400949f4` @ `400949f4`
```c

undefined4
FUN_400949f4(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  
  uVar1 = DAT_400804d0;
  memw();
  iVar2 = FUN_40083eac(param_3,DAT_400804d0);
  uVar3 = 0xffffffff;
  if (iVar2 != 0) {
    memw();
    iVar4 = FUN_40083eac(0x158,uVar1);
    if (iVar4 == 0) {
      uVar3 = 0xffffffff;
      FUN_40098804(iVar2);
    }
    else {
      *(int *)(iVar4 + 0x34) = iVar2;
      *(undefined1 *)(iVar4 + 0x155) = 0;
      memw();
      memw();
      FUN_40094478(param_1,param_2,param_3,param_4,param_5,param_6,iVar4,0,param_7);
      FUN_400947c0(iVar4,param_7);
      uVar3 = 1;
    }
  }
  return uVar3;
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
        enterState_RC();
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
// truncated
```

## `FUN_400d6224` @ `400d6224`
```c

undefined4 FUN_400d6224(undefined1 param_1)

{
  undefined4 uVar1;
  
  uVar1 = FUN_400d84b4(param_1);
  return uVar1;
}

```

## `FUN_4015e3c0` @ `4015e3c0`
```c

void FUN_4015e3c0(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 4) = param_2;
  return;
}

```

## `FUN_400d2dac` @ `400d2dac`
```c

void FUN_400d2dac(int param_1,char param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  ushort uVar4;
  undefined *puVar5;
  int aiStack_34 [3];
  undefined4 uStack_28;
  int iStack_24;
  
  iVar2 = DAT_400d0144;
  piVar1 = DAT_400d0130;
  memw();
  iStack_24 = *DAT_400d0130;
  memw();
  FUN_400d51fc(DAT_400d0144);
  iVar3 = 0;
  if (param_2 == '\0') goto LAB_400d2e12;
  iVar3 = FUN_400910b8(param_1,PTR_str_bitmapboot_400d0198);
  if (iVar3 == 0) {
    (*(code *)PTR_FUN_400d01c4)(iVar2,0,0,PTR_bitmap_boot_or_extra_data_400d019c,0x80,0x40,1);
  }
  while( true ) {
    FUN_400d56b4(iVar2);
    iVar3 = iStack_24;
    memw();
    memw();
    param_1 = *piVar1;
    if (iStack_24 == param_1) break;
    FUN_40082e5c();
LAB_400d2e12:
    uVar4 = (ushort)iVar3;
    FUN_400d4fd8(iVar2,1);
    puVar5 = PTR_str_by_emensta_400d01a0;
    *(undefined4 *)(iVar2 + 0x14) = DAT_400d0194;
    FUN_400d6084(aiStack_34,puVar5);
    if ((uStack_28 & 0x80000000) == 0) {
      if (aiStack_34[0] != 0) {
        uVar4 = (ushort)aiStack_34[2];
      }
    }
    else {
      uVar4 = uStack_28._3_1_ & 0x7f;
    }
    *(short *)(iVar2 + 0x10) = (short)(0x80 - (short)(uVar4 * 6) >> 1);
    *(undefined2 *)(iVar2 + 0x12) = 2;
    (*(code *)PTR_FUN_400d0174)(iVar2,aiStack_34);
    iVar3 = FUN_400910b8(param_1,table_bitmap_refs);
    puVar5 = PTR_bitmap1_data_400d01a8;
    if ((((iVar3 == 0) ||
         (iVar3 = FUN_400910b8(param_1,PTR_str_bitmap2_400d01ac), puVar5 = PTR_bitmap2_data_400d01b0
         , iVar3 == 0)) ||
        (iVar3 = FUN_400910b8(param_1,PTR_str_bitmap3_400d01b4), puVar5 = PTR_bitmap3_data_400d01b8,
        iVar3 == 0)) ||
       (iVar3 = FUN_400910b8(param_1,PTR_str_bitmap4_400d01bc), puVar5 = PTR_bitmap4_data_400d01c0,
       iVar3 == 0)) {
      (*(code *)PTR_FUN_400d01c4)(iVar2,0,0xc,puVar5,0x80,0x32,1);
    }
    FUN_400d5eec(aiStack_34);
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

## `Serial_println_empty` @ `400d5d1c`
```c

undefined4 Serial_println_empty(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = FUN_400d5ce8(param_1,PTR_s__3f406b34_0x23_400d0364);
  return uVar1;
}

```

## `FUN_400d670c` @ `400d670c`
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

## `FUN_4015e3c8` @ `4015e3c8`
```c

bool FUN_4015e3c8(int param_1)

{
  bool bVar1;
  
  bVar1 = false;
  if (*(int *)(param_1 + 0x10) == 0) {
    bVar1 = *(int *)(param_1 + 0x14) == 1;
  }
  return bVar1;
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
    Serial_print(DAT_400d0028,PTR_str_State4_RC_400d0124);
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

## `enterState_BT` @ `400d28d8`
```c

void enterState_BT(void)

{
  int *piVar1;
  undefined *puVar2;
  undefined4 uVar3;
  
  piVar1 = DAT_400d0108;
  if (*DAT_400d0108 != 1) {
    Serial_print(DAT_400d0028,table_state_strings);
    puVar2 = PTR_str_bitmap1_400d0110;
    *piVar1 = 1;
    FUN_400d2dac(puVar2,0);
    uVar3 = FUN_400d670c();
    *DAT_400d00fc = uVar3;
    *DAT_400d0100 = 0;
    *PTR_DAT_400d00f8 = 0;
    gpio_write_or_mode(0x1b);
    *(undefined4 *)PTR_DAT_400d0104 = 1;
  }
  statusLedBlink();
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
    Serial_print(DAT_400d0028,PTR_str_State2_BLE_400d0114);
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

## `enterState_WiFi` @ `400d2968`
```c

void enterState_WiFi(void)

{
  int *piVar1;
  undefined *puVar2;
  undefined4 uVar3;
  
  piVar1 = DAT_400d0108;
  if (*DAT_400d0108 != 3) {
    Serial_print(DAT_400d0028,PTR_str_State3_WiFi_400d011c);
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
  statusLedBlink();
  return;
}

```

## `FUN_400d2a24` @ `400d2a24`
```c

void FUN_400d2a24(void)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined *puVar6;
  int aiStack_34 [2];
  uint uStack_2c;
  uint uStack_28;
  int iStack_24;
  
  piVar2 = DAT_400d0130;
  piVar1 = DAT_400d0108;
  memw();
  iStack_24 = *DAT_400d0130;
  memw();
  if (*DAT_400d0108 != 0) {
    Serial_print(DAT_400d0028,PTR_str_State0_Idle_400d013c);
    *piVar1 = 0;
  }
  piVar1 = DAT_400d0140;
  *DAT_400d0140 = *DAT_400d0140 + 1;
  iVar4 = DAT_400d0144;
  FUN_400d51fc(DAT_400d0144);
  FUN_400d4fd8(iVar4,1);
  puVar6 = PTR_DAT_400d0148;
  *(undefined4 *)(iVar4 + 0x10) = 0;
  FUN_400d5d08(iVar4,puVar6);
  iVar3 = nrf_isChipConnected(DAT_400d0024);
  puVar6 = PTR_s_OK_3f406b01_0x11_400d0134;
  if (iVar3 == 0) {
    puVar6 = PTR_s_FAIL_3f40eb3c_0x1a_400d0138;
  }
  FUN_400d5d08(iVar4,puVar6);
  puVar6 = PTR_DAT_400d0150;
  *(undefined4 *)(iVar4 + 0x10) = DAT_400d014c;
  FUN_400d5d08(iVar4,puVar6);
  iVar3 = nrf_isChipConnected(DAT_400d0054);
  puVar6 = PTR_s_OK_3f406b01_0x11_400d0134;
  if (iVar3 == 0) {
    puVar6 = PTR_s_FAIL_3f40eb3c_0x1a_400d0138;
  }
  FUN_400d5d08(iVar4,puVar6);
  (*(code *)PTR_FUN_400d016c)(iVar4,0x3c,10,8,0xc,1);
  (*(code *)PTR_FUN_400d0170)(iVar4,0x3d,0xb,6,3,1);
  (*(code *)PTR_FUN_400d0170)(iVar4,0x38,0x10,0x10,2,1);
  (*(code *)PTR_FUN_400d0170)(iVar4,0x36,0x14,4,2,1);
  (*(code *)PTR_FUN_400d0170)(iVar4,0x3e,0x14,4,2,1);
  (*(code *)PTR_FUN_400d0170)(iVar4,0x46,0x14,4,2,1);
  FUN_400d4fd8(iVar4,1);
  puVar6 = PTR_DAT_400d0158;
  *(undefined4 *)(iVar4 + 0x10) = DAT_400d0154;
  FUN_400d5d08(iVar4,puVar6);
  uVar5 = (int)((longlong)*piVar1 * (longlong)DAT_400d015c >> 0x22) - (*piVar1 >> 0x1f) &
          DAT_400d0160;
  if ((int)uVar5 < 0) {
    uVar5 = (uVar5 - 1 | 0xfffffffc) + 1;
  }
  FUN_400d6084(aiStack_34,PTR_str_Connected_400d0164);
  for (iVar3 = 0; iVar3 < (int)uVar5; iVar3 = iVar3 + 1) {
    FUN_400d6100(aiStack_34,PTR_DAT_400d0168);
  }
  if ((uStack_28 & 0x80000000) != 0) goto LAB_400d2bf0;
  uVar5 = 0;
  if (aiStack_34[0] != 0) {
    uVar5 = uStack_2c;
  }
  while( true ) {
    *(short *)(iVar4 + 0x10) = (short)(uVar5 * -6 + 0x80 >> 1);
    *(undefined2 *)(iVar4 + 0x12) = 0x26;
    (*(code *)PTR_FUN_400d0174)(iVar4,aiStack_34);
    FUN_400d56b4(iVar4);
    FUN_400d5eec(aiStack_34);
    memw();
    memw();
    iVar4 = *piVar2;
// truncated
```

## `FUN_400d493c` @ `400d493c`
```c

undefined4 FUN_400d493c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  if (*(int *)(param_1 + 0x3c) == 0) {
    iVar1 = FUN_40093e48(1);
    *(int *)(param_1 + 0x3c) = iVar1;
    if (iVar1 == 0) {
      return 0;
    }
  }
  iVar1 = FUN_40094190(*(undefined4 *)(param_1 + 0x3c),0xffffffff);
  if (iVar1 != 1) {
    return 0;
  }
  if ((*(char *)(param_1 + 0x40) == '\0') &&
     ((iVar1 = FUN_400d63ac(*(undefined1 *)(param_1 + 0x10)), iVar1 != 0 ||
      (((iVar1 = FUN_400d48fc(param_1), iVar1 != 0 &&
        (iVar1 = (*(code *)PTR_FUN_400d02d8)(param_1,param_2,param_3), iVar1 != 0)) &&
       (iVar1 = FUN_400d63d0(*(undefined1 *)(param_1 + 0x10),(int)*(char *)(param_1 + 0x11),
                             (int)*(char *)(param_1 + 0x12),param_4), iVar1 == 0)))))) {
    uVar2 = 1;
  }
  else {
    FUN_400d48d8(param_1);
    uVar2 = 0;
  }
  FUN_40093c38(*(undefined4 *)(param_1 + 0x3c),0,0);
  return uVar2;
}

```

## `FUN_400d5220` @ `400d5220`
```c

undefined4 FUN_400d5220(int param_1,undefined1 param_2,char param_3,char param_4,char param_5)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  undefined *puVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  
  if (*(int *)(param_1 + 0x2c) == 0) {
    iVar3 = *(short *)(param_1 + 10) + 7;
    if (iVar3 < 0) {
      iVar3 = *(short *)(param_1 + 10) + 0xe;
    }
    iVar3 = FUN_400987e4((iVar3 >> 3) * (int)*(short *)(param_1 + 8));
    *(int *)(param_1 + 0x2c) = iVar3;
    if (iVar3 == 0) {
      return 0;
    }
  }
  FUN_400d51fc(param_1);
  iVar3 = (int)*(short *)(param_1 + 10);
  uVar6 = 0x20;
  if (iVar3 < 0x21) {
    iVar2 = *(short *)(param_1 + 8) + -0x73;
    iVar3 = (iVar3 + -0x20) - (iVar3 + -0x20 >> 0x1f);
    iVar2 = iVar2 - (iVar2 >> 0x1f);
    uVar5 = 0x73;
    puVar4 = PTR_DAT_400d02f8;
  }
  else {
    iVar2 = *(short *)(param_1 + 8) + -0x52;
    iVar3 = (iVar3 + -0x40) - (iVar3 + -0x40 >> 0x1f);
    iVar2 = iVar2 - (iVar2 >> 0x1f);
    uVar6 = 0x40;
    uVar5 = 0x52;
    puVar4 = PTR_DAT_400d02f4;
  }
  (*(code *)PTR_FUN_400d01c4)(param_1,iVar2 >> 1,iVar3 >> 1,puVar4,uVar5,uVar6,1);
  *(undefined1 *)(param_1 + 0x31) = param_2;
  if (*(int *)(param_1 + 0x28) == 0) {
    FUN_400d6198(*(undefined1 *)(param_1 + 0x35),3);
    FUN_400d6198(*(undefined1 *)(param_1 + 0x36),3);
    gpio_write_or_mode(*(undefined1 *)(param_1 + 0x36),1);
    if (*(int *)(param_1 + 0x24) == 0) {
      FUN_400d6198(*(undefined1 *)(param_1 + 0x33),3);
      FUN_400d6198(*(undefined1 *)(param_1 + 0x34),3);
      gpio_write_or_mode(*(undefined1 *)(param_1 + 0x34),0);
    }
    else if (param_5 != '\0') {
      spi_setPins(*(int *)(param_1 + 0x24),0xffffffff,0xffffffff,0xffffffff);
    }
  }
  else {
    if ((param_3 == '\0') && (param_3 = '=', *(short *)(param_1 + 10) == 0x20)) {
      param_3 = '<';
    }
    *(char *)(param_1 + 0x30) = param_3;
    if (param_5 != '\0') {
      FUN_400d493c(*(int *)(param_1 + 0x28),0xffffffff,0xffffffff,0);
    }
  }
  if ((param_4 != '\0') && (-1 < *(char *)(param_1 + 0x37))) {
    FUN_400d6198((int)*(char *)(param_1 + 0x37),3);
    gpio_write_or_mode(*(undefined1 *)(param_1 + 0x37),1);
    delay_ms(1);
    gpio_write_or_mode(*(undefined1 *)(param_1 + 0x37),0);
    delay_ms(10);
    gpio_write_or_mode(*(undefined1 *)(param_1 + 0x37),1);
  }
  if (*(int *)(param_1 + 0x28) == 0) {
    if (*(int *)(param_1 + 0x24) != 0) {
      FUN_400d3730(*(int *)(param_1 + 0x24),*(undefined4 *)(param_1 + 0x44),
                   *(undefined4 *)(param_1 + 0x48));
    }
    gpio_write_or_mode(*(undefined1 *)(param_1 + 0x36),0);
  }
  else {
// truncated
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
// truncated
```
