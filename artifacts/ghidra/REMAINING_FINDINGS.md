# Remaining Findings Pass

## Immediate scan app region 0x400D2000-0x400D4000
- imm **0**: 50 hits
- imm **2**: 33 hits
- imm **4**: 50 hits
- imm **5**: 19 hits
- imm **12**: 43 hits
- imm **13**: 7 hits
- imm **14**: 6 hits
- imm **15**: 6 hits
- imm **16**: 23 hits
  - 400d2a06  movi.n a11,0x10  in FUN_400d29f8
  - 400d2a6f  s32i.n a5,a2,0x10  in FUN_400d2a24
  - 400d2a99  s32i.n a5,a2,0x10  in FUN_400d2a24
  - 400d2ae2  movi.n a13,0x10  in FUN_400d2a24
  - 400d2b3b  s32i.n a5,a2,0x10  in FUN_400d2a24
  - 400d2baa  s16i a3,a2,0x10  in FUN_400d2a24
  - 400d2e51  s16i a3,a4,0x10  in FUN_400d2dac
  - 400d322c  movi.n a12,0x10  in FUN_400d3220
  - 400d3536  movi.n a11,0x10  in nrf_startConstCarrier
  - 400d35c4  movi.n a11,0x10  in FUN_400d3590
  - 400d35ea  s32i.n a8,a2,0x10  in spi_setBus
  - 400d3611  l32i a8,a2,0x10  in spi_setPins
  - 400d361c  s32i.n a10,a2,0x10  in spi_setPins
  - 400d361e  l32i.n a11,a2,0x10  in spi_setPins
  - 400d374f  l32i.n a8,a2,0x10  in FUN_400d3730
  - 400d375d  s32i a10,a2,0x10  in FUN_400d3730
  - 400d3766  l32i.n a11,a2,0x10  in FUN_400d3730
  - 400d37f4  s32i.n a10,a2,0x10  in FUN_400d37d8
  - 400d383a  s32i.n a8,a2,0x10  in FUN_400d380c
  - 400d3840  l32i.n a8,a2,0x10  in FUN_400d380c
  - 400d39f4  bnei a4,0x10,0x400d3a00  in ?
  - 400d3a83  movi.n a3,0x10  in ?
  - 400d3d7c  movi.n a4,0x10  in FUN_400d3ce4
- imm **18**: 5 hits
- imm **19**: 6 hits
- imm **21**: 3 hits
- imm **22**: 2 hits
  - 400d2a12  movi a11,0x16  in FUN_400d29f8
  - 400d3a4e  movi.n a3,0x16  in ?
- imm **23**: 4 hits
- imm **27**: 13 hits

## App cluster functions
Count: 71

### `radioTask` @ `400d236c`
```c

void radioTask(void)

{
  char *pcVar1;
  undefined4 uVar2;
  undefined *puVar3;
  undefined4 uVar4;
  undefined1 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  
  FUN_400d36e4(DAT_400d0020);
  delay_ms(2);
  uVar6 = (*(code *)PTR_FUN_400d0084)(0x20);
  spi_setBus(uVar6,2);
  spi_setPins(uVar6,0xe,0xc,0xd,0xf);
  delay_ms(5);
  uVar7 = (*(code *)PTR_FUN_400d0084)(0x20);
  spi_setBus(uVar7,3);
  spi_setPins(uVar7,0x12,0x13,0x17,0x15);
  delay_ms(5);
  uVar2 = DAT_400d0024;
  iVar8 = nrf_begin(DAT_400d0024,uVar6);
  puVar3 = PTR_s__________________________________400d002c;
  uVar6 = DAT_400d0028;
  if (iVar8 == 0) {
    Serial_println_empty(DAT_400d0028);
    Serial_print(uVar6,puVar3);
    Serial_println_empty(uVar6);
    Serial_print(uVar6,PTR_DAT_400d0044);
    Serial_print(uVar6,PTR_DAT_400d0048);
    Serial_print(uVar6,PTR_DAT_400d004c);
    Serial_println_empty(uVar6);
    Serial_print(uVar6,PTR_str_HSPI_FAIL_400d0050);
  }
  else {
    Serial_println_empty(DAT_400d0028);
    Serial_print(uVar6,puVar3);
    Serial_println_empty(uVar6);
    Serial_print(uVar6,PTR_DAT_400d0030);
    Serial_print(uVar6,PTR_DAT_400d0034);
    Serial_print(uVar6,PTR_DAT_400d0038);
    Serial_println_empty(uVar6);
    Serial_print(uVar6,PTR_str_HSPI_SUCCESS_400d003c);
    FUN_400d32c4(uVar2,0);
    FUN_400d3180(uVar2);
    FUN_400d34b0(uVar2,0);
    FUN_400d32f4(uVar2,3,1);
    FUN_400d3328(uVar2,1);
    FUN_400d3460(uVar2,0);
    nrf_startConstCarrier(uVar2,3,*PTR_DAT_400d0040);
  }
  uVar4 = DAT_400d0054;
  iVar8 = nrf_begin(DAT_400d0054,uVar7);
  if (iVar8 == 0) {
    Serial_println_empty(uVar6);
    Serial_print(uVar6,puVar3);
    Serial_println_empty(uVar6);
    Serial_print(uVar6,PTR_DAT_400d006c);
    Serial_print(uVar6,PTR_DAT_400d0070);
    Serial_print(uVar6,PTR_DAT_400d0074);
    Serial_println_empty(uVar6);
    Serial_print(uVar6,PTR_str_VSPI_FAIL_400d0078);
    pcVar1 = DAT_400d007c;
  }
  else {
    Serial_println_empty(uVar6);
// truncated
```

### `FUN_400d2714` @ `400d2714`
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

### `FUN_400d2844` @ `400d2844`
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

### `statusLedBlink` @ `400d2868`
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

### `enterState_BT` @ `400d28d8`
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

### `enterState_BLE` @ `400d2920`
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

### `enterState_WiFi` @ `400d2968`
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

### `enterState_RC` @ `400d29b0`
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

### `FUN_400d29f8` @ `400d29f8`
```c

void FUN_400d29f8(void)

{
  undefined4 uVar1;
  
  uVar1 = DAT_400d012c;
  FUN_400d30a8(DAT_400d0024,0x10,0xf,DAT_400d012c);
  FUN_400d30a8(DAT_400d0054,0x16,0x15,uVar1);
  FUN_400d37d8(DAT_400d009c,0);
  return;
}

```

### `FUN_400d2a24` @ `400d2a24`
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
// truncated
```

### `FUN_400d2d68` @ `400d2d68`
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

### `FUN_400d2dac` @ `400d2dac`
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

### `FUN_400d2f0c` @ `400d2f0c`
```c

void FUN_400d2f0c(void)

{
  FUN_400d5014(DAT_400d0144,0x80,0x40,DAT_400d018c,0xffffffff,DAT_400d01c8,DAT_400d01cc);
  return;
}

```

### `FUN_400d2f2c` @ `400d2f2c`
```c

void FUN_400d2f2c(void)

{
  FUN_400d4fec(DAT_400d0144);
  return;
}

```

### `FUN_400d2f38` @ `400d2f38`
```c

void FUN_400d2f38(int param_1,undefined1 param_2)

{
  gpio_write_or_mode(*(undefined1 *)(param_1 + 5),param_2);
  FUN_400d6730(*(undefined4 *)(param_1 + 0x24));
  return;
}

```

### `FUN_400d2f4c` @ `400d2f4c`
```c

void FUN_400d2f4c(int param_1,undefined1 param_2)

{
  if (*(char *)(param_1 + 5) != *(char *)(param_1 + 4)) {
    gpio_write_or_mode(*(char *)(param_1 + 4),param_2);
  }
  return;
}

```

### `FUN_400d2f60` @ `400d2f60`
```c

void FUN_400d2f60(undefined4 *param_1)

{
  FUN_400d3730(*param_1,param_1[2],1);
  FUN_400d2f38(param_1,0);
  return;
}

```

### `FUN_400d2f7c` @ `400d2f7c`
```c

void FUN_400d2f7c(undefined4 *param_1)

{
  FUN_400d2f38(param_1,1);
  FUN_400d3778(*param_1);
  return;
}

```

### `FUN_400d2f90` @ `400d2f90`
```c

void FUN_400d2f90(undefined4 *param_1,undefined1 param_2,undefined1 *param_3,char param_4)

{
  undefined1 uVar1;
  
  FUN_400d2f60(param_1);
  uVar1 = FUN_400d379c(*param_1,param_2);
  *(undefined1 *)(param_1 + 3) = uVar1;
  while (param_4 = param_4 + -1, param_4 != -1) {
    uVar1 = FUN_400d379c(*param_1,0xff);
    *param_3 = uVar1;
    param_3 = param_3 + 1;
  }
  FUN_400d2f7c(param_1);
  return;
}

```

### `FUN_400d2fcc` @ `400d2fcc`
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

### `FUN_400d2ff8` @ `400d2ff8`
```c

void FUN_400d2ff8(undefined4 *param_1,byte param_2,undefined1 *param_3,char param_4)

{
  undefined1 uVar1;
  
  FUN_400d2f60(param_1);
  uVar1 = FUN_400d379c(*param_1,param_2 | 0x20);
  *(undefined1 *)(param_1 + 3) = uVar1;
  while (param_4 = param_4 + -1, param_4 != -1) {
    uVar1 = *param_3;
    param_3 = param_3 + 1;
    FUN_400d379c(*param_1,uVar1);
  }
  FUN_400d2f7c(param_1);
  return;
}

```

### `FUN_400d3034` @ `400d3034`
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

### `FUN_400d3060` @ `400d3060`
```c

undefined1 FUN_400d3060(int param_1)

{
  FUN_400d2f90(param_1,0xe2,0);
  return *(undefined1 *)(param_1 + 0xc);
}

```

### `FUN_400d3078` @ `400d3078`
```c

undefined1 FUN_400d3078(int param_1)

{
  FUN_400d2f90(param_1,0xe1,0);
  return *(undefined1 *)(param_1 + 0xc);
}

```

### `FUN_400d3090` @ `400d3090`
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

### `FUN_400d30a8` @ `400d30a8`
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

### `nrf_setChannel` @ `400d30d8`
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

### `FUN_400d30f0` @ `400d30f0`
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
    FUN_400d3034(param_1,iVar1,*(undefined1 *)(param_1 + 0xd));
    iVar1 = iVar2;
  } while (iVar2 != 0x17);
  return;
}

```

### `nrf_isChipConnected` @ `400d3120`
```c

bool nrf_isChipConnected(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_400d2fcc(param_1,3);
  return *(byte *)(param_1 + 0x1c) - 2 == iVar1;
}

```

### `FUN_400d3144` @ `400d3144`
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

### `FUN_400d3180` @ `400d3180`
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

### `FUN_400d31d8` @ `400d31d8`
```c

void FUN_400d31d8(int param_1)

{
  FUN_400d2f4c(param_1,0);
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfd;
  FUN_400d3034(param_1,0);
  return;
}

```

### `FUN_400d31fc` @ `400d31fc`
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

### `FUN_400d3220` @ `400d3220`
```c

void FUN_400d3220(undefined4 param_1)

{
  FUN_400d2f4c(param_1,0);
  FUN_400d3034(param_1,7,0x10);
  FUN_400d2f90(param_1,0xe3,0);
  FUN_400d2f4c(param_1,1);
  return;
}

```

### `FUN_400d3248` @ `400d3248`
```c

void FUN_400d3248(int param_1,char param_2)

{
  byte bVar1;
  
  if ((byte)(param_2 - 2U) == 0) {
    FUN_400d3034(param_1,3);
    *(undefined1 *)(param_1 + 0x1c) = 2;
  }
  else {
    bVar1 = param_2 - 2U & 3;
    FUN_400d3034(param_1,3,bVar1);
    *(byte *)(param_1 + 0x1c) = bVar1 + 2;
  }
  return;
}

```

### `FUN_400d327c` @ `400d327c`
```c

void FUN_400d327c(undefined4 *param_1)

{
  undefined1 uVar1;
  
  FUN_400d2f60(param_1);
  uVar1 = FUN_400d379c(*param_1,0x50);
  *(undefined1 *)(param_1 + 3) = uVar1;
  FUN_400d379c(*param_1,0x73);
  FUN_400d2f7c(param_1);
  return;
}

```

### `FUN_400d32a0` @ `400d32a0`
```c

void FUN_400d32a0(int param_1)

{
  uint uVar1;
  
  if (*(char *)(param_1 + 0x1b) != '\0') {
    uVar1 = FUN_400d2fcc(param_1,0x1d);
    FUN_400d3034(param_1,0x1d,uVar1 & 0xfd);
    *(undefined1 *)(param_1 + 0x1b) = 0;
  }
  return;
}

```

### `FUN_400d32c4` @ `400d32c4`
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

### `FUN_400d32f4` @ `400d32f4`
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

### `FUN_400d3328` @ `400d3328`
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

### `FUN_400d337c` @ `400d337c`
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

### `nrf_begin` @ `400d3448`
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

### `FUN_400d3460` @ `400d3460`
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

### `FUN_400d3494` @ `400d3494`
```c

void FUN_400d3494(int param_1)

{
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xf7;
  FUN_400d3034(param_1,0);
  return;
}

```

### `FUN_400d34b0` @ `400d34b0`
```c

void FUN_400d34b0(undefined4 param_1,byte param_2,byte param_3)

{
  FUN_400d3034(param_1,4,
               ((param_2 < 0xf) * param_2 + (param_2 >= 0xf) * '\x0f') * '\x10' |
               (param_3 < 0xf) * param_3 + (param_3 >= 0xf) * '\x0f');
  return;
}

```

### `nrf_startConstCarrier` @ `400d34d8`
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

### `FUN_400d3590` @ `400d3590`
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

### `spi_setBus` @ `400d35d0`
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

### `spi_setPins` @ `400d35fc`
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

### `FUN_400d36a4` @ `400d36a4`
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

### `FUN_400d36e4` @ `400d36e4`
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

### `FUN_400d371c` @ `400d371c`
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

### `FUN_400d3730` @ `400d3730`
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

### `FUN_400d3778` @ `400d3778`
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

### `FUN_400d379c` @ `400d379c`
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

### `FUN_400d37cc` @ `400d37cc`
```c

void FUN_400d37cc(void)

{
  FUN_400d371c(DAT_400d0020);
  return;
}

```

### `FUN_400d37d8` @ `400d37d8`
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

### `FUN_400d380c` @ `400d380c`
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

### `FUN_400d38a0` @ `400d38a0`
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

### `FUN_400d38cc` @ `400d38cc`
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

### `FUN_400d38e8` @ `400d38e8`
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

### `FUN_400d3908` @ `400d3908`
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

### `FUN_400d3b94` @ `400d3b94`
```c

void FUN_400d3b94(void)

{
  int *piVar1;
  undefined *puVar2;
  int iVar3;
  byte *pbVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined1 auStack_2c [8];
  undefined4 *puStack_24;
  
  pbVar4 = DAT_400d021c;
  puVar5 = DAT_400d0130;
  memw();
  puStack_24 = (undefined4 *)*DAT_400d0130;
  memw();
  if (*DAT_400d021c != 0) goto LAB_400d3be3;
  *DAT_400d021c = 1;
  iVar3 = FUN_400fe3a0(auStack_2c);
  if (iVar3 == 0) {
    FUN_400fe31c(auStack_2c);
  }
  iVar3 = FUN_400e4aa4();
  *pbVar4 = iVar3 == 0;
  piVar1 = DAT_400d0220;
  if (iVar3 != 0) goto LAB_400d3be3;
  puVar6 = (undefined4 *)0x0;
  if (*DAT_400d0220 != 0) goto LAB_400d3c01;
  iVar3 = FUN_40093544();
  *piVar1 = iVar3;
  puVar7 = puVar6;
  if (iVar3 != 0) goto LAB_400d3bfb;
LAB_400d3be0:
  *pbVar4 = (byte)puVar7;
LAB_400d3be3:
  puVar6 = puStack_24;
  memw();
  memw();
  puVar5 = (undefined4 *)*puVar5;
  pbVar4 = (byte *)(uint)*pbVar4;
  if (puStack_24 == puVar5) {
    return;
  }
  iVar3 = FUN_40082e5c();
LAB_400d3bfb:
  FUN_400936d0(iVar3,DAT_400d00e8);
LAB_400d3c01:
  piVar1 = DAT_400d0204;
  if (*DAT_400d0204 == 0) goto LAB_400d3cb2;
  goto LAB_400d3c09;
LAB_400d3cb2:
  iVar3 = FUN_40093b10(0x20,4);
  *piVar1 = iVar3;
  puVar7 = puVar6;
  if (iVar3 != 0) {
LAB_400d3c09:
    iVar3 = (*(code *)PTR_FUN_400d0238)();
    piVar1 = DAT_400d0224;
    puVar7 = (undefined4 *)(uint)(iVar3 != 0 && iVar3 != 0x103);
    if (((puVar7 == (undefined4 *)0x0) &&
        (((*DAT_400d0224 != 0 ||
          (FUN_400d66e4(PTR_FUN_400d0234,PTR_s_arduino_events_400d0230,DAT_400d022c,0,0x13,
                        DAT_400d0224,1), puVar7 = puVar6, *piVar1 != 0)) &&
         (puVar2 = PTR_LAB_400d0228,
         iVar3 = (*(code *)PTR_FUN_400d023c)
                           (*(undefined4 *)PTR_PTR_400d0208,0xffffffff,PTR_LAB_400d0228,0),
         puVar7 = puVar6, iVar3 == 0)))) &&
// truncated
```

### `FUN_400d3ce4` @ `400d3ce4`
```c

char FUN_400d3ce4(char param_1)

{
  undefined4 *puVar1;
  int *piVar2;
  char cVar3;
  int iVar4;
  char *pcVar5;
  undefined *puStack_188;
  undefined *puStack_184;
  undefined1 auStack_180 [108];
  undefined4 uStack_114;
  undefined4 uStack_110;
  undefined4 uStack_10c;
  undefined4 uStack_108;
  undefined4 uStack_104;
  undefined4 uStack_100;
  undefined4 uStack_fc;
  undefined4 uStack_f8;
  undefined4 uStack_f4;
  undefined4 uStack_ec;
  undefined4 uStack_e4;
  undefined4 uStack_dc;
  undefined4 uStack_d8;
  undefined4 uStack_d0;
  undefined4 uStack_cc;
  undefined4 uStack_c4;
  undefined4 uStack_c0;
  undefined4 auStack_b4 [36];
  char *pcStack_24;
  
  pcVar5 = DAT_400d0240;
  puVar1 = DAT_400d0130;
  memw();
  pcStack_24 = (char *)*DAT_400d0130;
  memw();
  if (*DAT_400d0240 != '\0') goto LAB_400d3e00;
  *DAT_400d0240 = '\x01';
  iVar4 = FUN_400d3b94();
  cVar3 = '\0';
  if (iVar4 != 0) goto LAB_400d3d29;
  do {
    *pcVar5 = '\0';
    while( true ) {
      memw();
      memw();
      pcVar5 = (char *)*puVar1;
      if (pcStack_24 == pcVar5) {
        return cVar3;
      }
      FUN_40082e5c();
LAB_400d3d29:
      piVar2 = DAT_400d0200;
      if (DAT_400d0200[1] == 0) {
        iVar4 = FUN_400ea328();
        piVar2[1] = iVar4;
      }
      if (*piVar2 == 0) {
        iVar4 = FUN_400ea360();
        *piVar2 = iVar4;
      }
      FUN_40090d70(&uStack_10c,0,0x54);
      uStack_e4 = 6;
      uStack_dc = 0x2f0;
      puStack_188 = PTR_FUN_400d0244;
      uStack_c4 = 7;
      puStack_184 = PTR_DAT_400d0248;
      uStack_c0 = DAT_400d024c;
      uStack_114 = 8;
// truncated
```

### `FUN_400d3e08` @ `400d3e08`
```c

undefined4 FUN_400d3e08(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (*DAT_400d0220 != 0) {
    uVar1 = FUN_400936d0(*DAT_400d0220,param_1);
  }
  return uVar1;
}

```

### `FUN_400d3e20` @ `400d3e20`
```c

undefined4 FUN_400d3e20(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (*DAT_400d0220 != 0) {
    uVar1 = FUN_40093684(*DAT_400d0220,param_1);
  }
  return uVar1;
}

```

### `FUN_400d3e38` @ `400d3e38`
```c

undefined4 FUN_400d3e38(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 auStack_24 [9];
  
  uVar2 = 0;
  if ((*DAT_400d0240 != '\0') && (*DAT_400d025c != '\0')) {
    iVar1 = FUN_40126708(auStack_24);
    uVar2 = 0;
    if (iVar1 == 0) {
      uVar2 = auStack_24[0];
    }
  }
  return uVar2;
}

```

### `FUN_400d3f4c` @ `400d3f4c`
```c

undefined4 FUN_400d3f4c(undefined4 param_1,uint param_2)

{
  uint uVar1;
  undefined4 uVar2;
  
  uVar1 = FUN_400d3e38();
  uVar2 = 1;
  if ((uVar1 & 1) != (param_2 & 0xff)) {
    if ((param_2 & 0xff) == 0) {
      uVar1 = uVar1 & 0xfffffffe;
    }
    else {
      uVar1 = uVar1 | 1;
    }
    uVar2 = FUN_400d3e5c(uVar1);
  }
  return uVar2;
}

```

## pinMode callers (FUN_400d6198)
Caller count: 12

### pinMode caller `FUN_400d37d8` @ `400d37d8`
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

### pinMode caller `FUN_400d3144` @ `400d3144`
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

### pinMode caller `FUN_400d6860` @ `400d6860`
```c

void FUN_400d6860(int param_1,char param_2)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  
  if (param_1 != 0) {
    if (param_2 < '\0') {
      param_2 = '\f';
      if ((*(char *)(param_1 + 8) != '\x02') && (param_2 = '\x13', *(char *)(param_1 + 8) != '\x03')
         ) {
        param_2 = '\a';
      }
    }
    do {
      iVar2 = FUN_40094190(*(undefined4 *)(param_1 + 4),0xffffffff);
    } while (iVar2 != 1);
    FUN_400d6198((int)param_2,1);
    bVar1 = *(byte *)(param_1 + 8);
    uVar3 = 1;
    if (((1 < bVar1) && (uVar3 = 9, bVar1 != 2)) && (uVar3 = 0x40, bVar1 != 3)) {
      uVar3 = 0;
    }
    FUN_400d7c70((int)param_2,uVar3,0);
    FUN_40093c38(*(undefined4 *)(param_1 + 4),0,0);
  }
  return;
}

```

### pinMode caller `FUN_400d6a5c` @ `400d6a5c`
```c

void FUN_400d6a5c(int param_1,uint param_2,char param_3)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  param_2 = param_2 & 0xff;
  if (2 < param_2) {
    return;
  }
  if (param_1 == 0) {
    return;
  }
  if (param_3 < '\0') {
    param_3 = '\x0f';
    param_2 = 0;
    if ((*(char *)(param_1 + 8) != '\x02') && (param_3 = '\x05', *(char *)(param_1 + 8) != '\x03'))
    {
      param_3 = '\v';
    }
  }
  FUN_400d6198((int)param_3,3);
  cVar1 = *(char *)(param_1 + 8);
  if ((cVar1 == '\0') || (cVar1 == '\x01')) {
    uVar2 = 5;
    if ((param_2 != 0) && (uVar2 = 6, param_2 != 1)) {
      uVar2 = 7;
    }
  }
  else {
    if (cVar1 == '\x02') {
      uVar2 = 0xb;
      if (param_2 == 0) goto LAB_400d6ab0;
      uVar3 = 0x3d;
      uVar2 = 0x3e;
    }
    else {
      uVar2 = 0;
      if ((cVar1 != '\x03') || (uVar2 = 0x44, param_2 == 0)) goto LAB_400d6ab0;
      uVar3 = 0x45;
      uVar2 = 0x46;
    }
    if (param_2 == 1) {
      uVar2 = uVar3;
    }
  }
LAB_400d6ab0:
  FUN_400d7c40((int)param_3,uVar2,0);
  FUN_400d6a20(param_1,1 << 0x20 - (0x20 - (param_2 & 0x1f)));
  return;
}

```

### pinMode caller `FUN_400d5220` @ `400d5220`
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
    FUN_400d4a4c(*(int *)(param_1 + 0x28),*(undefined4 *)(param_1 + 0x38));
  }
  FUN_400d5130(param_1,PTR_DAT_400d02fc,4);
  FUN_400d505c(param_1,*(char *)(param_1 + 10) + -1);
  FUN_400d5130(param_1,PTR_DAT_400d0300,4);
  uVar6 = 0x14;
  if (*(char *)(param_1 + 0x31) == '\x01') {
    uVar6 = 0x10;
  }
  FUN_400d505c(param_1,uVar6);
// truncated
```

### pinMode caller `FUN_400d2714` @ `400d2714`
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

## Callers of setup / loop / radioTask

### Target 0x400d2714
- from 400d795a type=UNCONDITIONAL_CALL in literal/data

### Target 0x400d2bfc
- from 400d7969 type=UNCONDITIONAL_CALL in literal/data

### Target 0x400d236c
- from 400d00f0 type=DATA in literal/data

### Target 0x400d2d68
- from 400d274f type=UNCONDITIONAL_CALL in FUN_400d2714@400d2714
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
// truncated
```

### Target 0x400d2f4c
- from 400d3172 type=UNCONDITIONAL_CALL in FUN_400d3144@400d3144
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
- from 400d3188 type=UNCONDITIONAL_CALL in FUN_400d3180@400d3180
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
- from 400d31e1 type=UNCONDITIONAL_CALL in FUN_400d31d8@400d31d8
```c

void FUN_400d31d8(int param_1)

{
  FUN_400d2f4c(param_1,0);
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfd;
  FUN_400d3034(param_1,0);
  return;
}

```
- from 400d3227 type=UNCONDITIONAL_CALL in FUN_400d3220@400d3220
```c

void FUN_400d3220(undefined4 param_1)

{
  FUN_400d2f4c(param_1,0);
  FUN_400d3034(param_1,7,0x10);
  FUN_400d2f90(param_1,0xe3,0);
  FUN_400d2f4c(param_1,1);
  return;
}

```
- from 400d3243 type=UNCONDITIONAL_CALL in FUN_400d3220@400d3220
```c

void FUN_400d3220(undefined4 param_1)

{
  FUN_400d2f4c(param_1,0);
  FUN_400d3034(param_1,7,0x10);
  FUN_400d2f90(param_1,0xe3,0);
  FUN_400d2f4c(param_1,1);
  return;
}

```
- from 400d356b type=UNCONDITIONAL_CALL in nrf_startConstCarrier@400d34d8
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
- from 400d35b1 type=UNCONDITIONAL_CALL in FUN_400d3590@400d3590
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

## Absolute pointer locations for key functions
- fn 0x400D2714 ptr at 0x3F417B2C (DROM)
- fn 0x400D2BFC ptr at 0x3F417BF0 (DROM)
- fn 0x400D236C ptr at 0x3F417B10 (DROM)
- fn 0x400D236C ptr at 0x400D00F0 (IROM)
- fn 0x400D2D68 ptr at 0x3F417C28 (DROM)
- fn 0x400D28D8 ptr at 0x3F417B64 (DROM)

## Extra helper decompilation

### `FUN_400d6d08` @ `400d6d08`
```c

int * FUN_400d6d08(uint param_1,undefined4 param_2,undefined1 param_3,undefined1 param_4)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  
  param_1 = param_1 & 0xff;
  if (param_1 < 4) {
    piVar1 = (int *)(PTR_DAT_400d0418 + param_1 * 0xc);
    if (piVar1[1] == 0) {
      iVar2 = FUN_40093e48(1);
      piVar1[1] = iVar2;
      if (iVar2 == 0) goto LAB_400d6d19;
    }
    puVar5 = DAT_400d041c;
    if (param_1 == 2) {
      uVar3 = FUN_40084444(DAT_400d041c);
      memw();
      *puVar5 = uVar3 | 0x40;
      puVar5 = DAT_400d0420;
      uVar4 = FUN_40084444(DAT_400d0420);
      uVar3 = 0xffffffbf;
    }
    else if (param_1 == 3) {
      uVar3 = FUN_40084444(DAT_400d041c);
      memw();
      *puVar5 = uVar3 | DAT_400d0424;
      puVar5 = DAT_400d0420;
      uVar4 = FUN_40084444(DAT_400d0420);
      uVar3 = DAT_400d0428;
    }
    else {
      uVar3 = FUN_40084444(DAT_400d041c);
      memw();
      *puVar5 = uVar3 | 2;
      puVar5 = DAT_400d0420;
      uVar4 = FUN_40084444(DAT_400d0420);
      uVar3 = 0xfffffffd;
    }
    memw();
    *puVar5 = uVar4 & uVar3;
    do {
      iVar2 = FUN_40094190(*(undefined4 *)(PTR_DAT_400d0418 + param_1 * 0xc + 4),0xffffffff);
    } while (iVar2 != 1);
    iVar2 = *piVar1;
    memw();
    memw();
    *(uint *)(iVar2 + 0x38) = *(uint *)(iVar2 + 0x38) & 0xffffffef;
    memw();
    *(undefined4 *)(iVar2 + 0x38) = 0;
    memw();
// truncated
```

### `FUN_400d7038` @ `400d7038`
```c

uint FUN_400d7038(uint param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  
  uVar1 = FUN_400d7c1c();
  uVar3 = DAT_400d0440;
  if ((param_1 < uVar1) &&
     (uVar3 = DAT_400d043c,
     uVar1 / (((DAT_400d043c >> 0x12 & 0x1fff) + 1) * ((DAT_400d043c >> 0xc & 0x3f) + 1)) <= param_1
     )) {
    uVar8 = 1;
    uVar6 = 0;
    uVar2 = 0;
    do {
      uVar7 = uVar8 << 0xc;
      uVar8 = uVar8 + 1;
      uVar4 = (uVar1 / uVar8) / param_1 - 2;
      uVar3 = DAT_400d0448;
      if (DAT_400d0444 < (int)uVar4) {
LAB_400d7087:
        uVar7 = uVar7 | uVar3;
      }
      else {
        if (0 < (int)uVar4) {
          uVar7 = uVar7 & DAT_400d044c;
          uVar3 = (uVar4 & 0x1fff) << 0x12;
          goto LAB_400d7087;
        }
        uVar7 = uVar7 & DAT_400d044c;
      }
      uVar4 = uVar7 & 0xffffffc0 | uVar8 >> 1;
      uVar7 = uVar1 / (((uVar7 >> 0x12 & 0x1fff) + 1) * uVar8);
      uVar3 = uVar4;
      if ((uVar7 != param_1) && (uVar3 = uVar2, (int)uVar7 < (int)param_1)) {
        iVar5 = param_1 - uVar7;
        iVar9 = param_1 - uVar6;
        if (iVar5 < 1) {
          iVar5 = -iVar5;
        }
        if (iVar9 < 1) {
          iVar9 = -iVar9;
        }
        if (iVar5 < iVar9) {
          uVar3 = uVar4;
          uVar6 = uVar7;
// truncated
```

### `FUN_400d2f38` @ `400d2f38`
```c

void FUN_400d2f38(int param_1,undefined1 param_2)

{
  gpio_write_or_mode(*(undefined1 *)(param_1 + 5),param_2);
  FUN_400d6730(*(undefined4 *)(param_1 + 0x24));
  return;
}

```

### `FUN_400d2ff8` @ `400d2ff8`
```c

void FUN_400d2ff8(undefined4 *param_1,byte param_2,undefined1 *param_3,char param_4)

{
  undefined1 uVar1;
  
  FUN_400d2f60(param_1);
  uVar1 = FUN_400d379c(*param_1,param_2 | 0x20);
  *(undefined1 *)(param_1 + 3) = uVar1;
  while (param_4 = param_4 + -1, param_4 != -1) {
    uVar1 = *param_3;
    param_3 = param_3 + 1;
    FUN_400d379c(*param_1,uVar1);
  }
  FUN_400d2f7c(param_1);
  return;
}

```

### `FUN_400d3078` @ `400d3078`
```c

undefined1 FUN_400d3078(int param_1)

{
  FUN_400d2f90(param_1,0xe1,0);
  return *(undefined1 *)(param_1 + 0xc);
}

```

### `FUN_400d3060` @ `400d3060`
```c

undefined1 FUN_400d3060(int param_1)

{
  FUN_400d2f90(param_1,0xe2,0);
  return *(undefined1 *)(param_1 + 0xc);
}

```

### `FUN_400d30f0` @ `400d30f0`
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
    FUN_400d3034(param_1,iVar1,*(undefined1 *)(param_1 + 0xd));
    iVar1 = iVar2;
  } while (iVar2 != 0x17);
  return;
}

```

### `FUN_400d3248` @ `400d3248`
```c

void FUN_400d3248(int param_1,char param_2)

{
  byte bVar1;
  
  if ((byte)(param_2 - 2U) == 0) {
    FUN_400d3034(param_1,3);
    *(undefined1 *)(param_1 + 0x1c) = 2;
  }
  else {
    bVar1 = param_2 - 2U & 3;
    FUN_400d3034(param_1,3,bVar1);
    *(byte *)(param_1 + 0x1c) = bVar1 + 2;
  }
  return;
}

```

### `FUN_400d327c` @ `400d327c`
```c

void FUN_400d327c(undefined4 *param_1)

{
  undefined1 uVar1;
  
  FUN_400d2f60(param_1);
  uVar1 = FUN_400d379c(*param_1,0x50);
  *(undefined1 *)(param_1 + 3) = uVar1;
  FUN_400d379c(*param_1,0x73);
  FUN_400d2f7c(param_1);
  return;
}

```

### `FUN_400d3494` @ `400d3494`
```c

void FUN_400d3494(int param_1)

{
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xf7;
  FUN_400d3034(param_1,0);
  return;
}

```

### `FUN_400d3220` @ `400d3220`
```c

void FUN_400d3220(undefined4 param_1)

{
  FUN_400d2f4c(param_1,0);
  FUN_400d3034(param_1,7,0x10);
  FUN_400d2f90(param_1,0xe3,0);
  FUN_400d2f4c(param_1,1);
  return;
}

```

### `FUN_400d380c` @ `400d380c`
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

### `FUN_400d2844` @ `400d2844`
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

### `FUN_400d6224` @ `400d6224`
```c

undefined4 FUN_400d6224(undefined1 param_1)

{
  undefined4 uVar1;
  
  uVar1 = FUN_400d84b4(param_1);
  return uVar1;
}

```

### `FUN_400d670c` @ `400d670c`
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

### `FUN_400949f4` @ `400949f4`
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

### `FUN_400d5ac4` @ `400d5ac4`
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
// truncated
```

### `FUN_400d493c` @ `400d493c`
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

### `FUN_400d5220` @ `400d5220`
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
// truncated
```

### `FUN_400d63ac` @ `400d63ac`
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

### `FUN_400d63d0` @ `400d63d0`
```c

int FUN_400d63d0(uint param_1,char param_2,char param_3,uint param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  int iVar4;
  char *pcVar5;
  undefined4 local_3c;
  int iStack_38;
  int iStack_34;
  undefined2 uStack_30;
  undefined1 auStack_2e [2];
  int iStack_2c;
  
  param_1 = param_1 & 0xff;
  iVar4 = 0x102;
  if (param_1 < 2) {
    iVar4 = DAT_400d03b8 + param_1 * 0xc;
    memw();
    if (*(int *)(iVar4 + 8) == 0) {
      uVar2 = FUN_40093e48(1);
      memw();
      *(undefined4 *)(iVar4 + 8) = uVar2;
      memw();
      if (*(int *)(iVar4 + 8) == 0) {
        return 0x101;
      }
    }
    pcVar5 = (char *)(DAT_400d03b8 + param_1 * 0xc);
    memw();
    iVar1 = FUN_40094190(*(undefined4 *)(pcVar5 + 8),0xffffffff);
    iVar4 = -1;
    if (iVar1 == 1) {
      memw();
      iVar4 = -1;
      if (*pcVar5 == '\0') {
        iVar1 = DAT_400d01cc;
        if (param_4 != 0) {
          iVar1 = (param_4 < DAT_400d01e0) * param_4 + (param_4 >= DAT_400d01e0) * DAT_400d01e0;
        }
        FUN_40090d70(auStack_2e,0,0xe);
        iStack_34 = (int)param_3;
        iStack_38 = (int)param_2;
        local_3c = 1;
        uStack_30 = 0x101;
        iStack_2c = iVar1;
        iVar4 = FUN_400d9204(param_1,&local_3c);
        if ((iVar4 == 0) && (iVar4 = FUN_400d8ca4(param_1,local_3c,0,0,0), iVar4 == 0)) {
          puVar3 = (undefined1 *)(DAT_400d03b8 + param_1 * 0xc);
          memw();
          *puVar3 = 1;
          uVar2 = DAT_400d03bc;
          memw();
// truncated
```

### `FUN_400d48fc` @ `400d48fc`
```c

undefined4 FUN_400d48fc(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x18) == 0) {
    iVar1 = FUN_400987e4(*(undefined4 *)(param_1 + 0x14));
    *(int *)(param_1 + 0x18) = iVar1;
    if (iVar1 == 0) {
      return 0;
    }
  }
  if (*(int *)(param_1 + 0x24) == 0) {
    iVar1 = FUN_400987e4(*(undefined4 *)(param_1 + 0x14));
    *(int *)(param_1 + 0x24) = iVar1;
    if (iVar1 == 0) {
      FUN_400d48d8(param_1);
      return 0;
    }
  }
  return 1;
}

```

### `FUN_400d36a4` @ `400d36a4`
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

## Possible constructors (assign +4 and +5)

### ctor-like `FUN_400d2f4c` @ `400d2f4c`
```c

void FUN_400d2f4c(int param_1,undefined1 param_2)

{
  if (*(char *)(param_1 + 5) != *(char *)(param_1 + 4)) {
    gpio_write_or_mode(*(char *)(param_1 + 4),param_2);
  }
  return;
}

```

### ctor-like `FUN_400d30a8` @ `400d30a8`
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

### ctor-like `FUN_400d3144` @ `400d3144`
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

Ctor-like count: 3

## Literal pool 0x400D0020-0x400D0280
- 0x400D0020 -> 0x3FFC3BFC DRAM/BSS
- 0x400D0024 -> 0x3FFC3B88 DRAM/BSS
- 0x400D0028 -> 0x3FFC3DC0 DRAM/BSS
- 0x400D002C -> 0x3F400120 STR ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
- 0x400D0030 -> 0x3F4001A5 STR .
- 0x400D0034 -> 0x3F400206 STR .
- 0x400D0038 -> 0x3F400265 STR .
- 0x400D003C -> 0x3F4002C4 STR Hardware Serial Peripheral Interface started !!! H
- 0x400D0040 -> 0x3FFBDB74 DRAM/BSS
- 0x400D0044 -> 0x3F40035E STR .
- 0x400D0048 -> 0x3F4003AE STR .
- 0x400D004C -> 0x3F400400 STR .
- 0x400D0050 -> 0x3F40044A STR !!! Hardware Serial Peripheral Interface start fai
- 0x400D0054 -> 0x3FFC3B60 DRAM/BSS
- 0x400D0058 -> 0x3F4004E4 STR .
- 0x400D005C -> 0x3F400546 STR .
- 0x400D0060 -> 0x3F4005A8 STR  .
- 0x400D0064 -> 0x3F400608 STR Variable Serial Peripheral Interface started !!! V
- 0x400D0068 -> 0x3FFBDB70 DRAM/BSS
- 0x400D006C -> 0x3F4006A2 STR .
- 0x400D0070 -> 0x3F4006F3 STR .
- 0x400D0074 -> 0x3F400748 STR  .
- 0x400D0078 -> 0x3F400793 STR !!! Variable Serial Peripheral Interface start fai
- 0x400D007C -> 0x3FFC3B38 DRAM/BSS
- 0x400D0080 -> 0x3FFBDB7C DRAM/BSS
- 0x400D0084 -> 0x4014EDB8 FN FUN_4014edb8
- 0x400D0088 -> 0x4014F5E4 FN FUN_4014f5e4
- 0x400D008C -> 0x4014FF20 FN FUN_4014ff20
- 0x400D0090 -> 0x0800001C 
- 0x400D0094 -> 0x0001C200 IMM 115200
- 0x400D0098 -> 0x00004E20 IMM 20000
- 0x400D009C -> 0x3FFC3B3C DRAM/BSS
- 0x400D00A0 -> 0x3F40082D STR bitmapboot
- 0x400D00A4 -> 0x3F400838 STR ##################################################
- 0x400D00A8 -> 0x3F4008BD STR .
- 0x400D00AC -> 0x3F4009E8 STR .
- 0x400D00B0 -> 0x3F400AD5 STR .
- 0x400D00B4 -> 0x3F400C06 STR .
- 0x400D00B8 -> 0x3F400CEB STR .
- 0x400D00BC -> 0x3F400E16 STR                                           Firmware
- 0x400D00C0 -> 0x3F400E9B STR                         .
- 0x400D00C4 -> 0x3F400FA6 STR                         .
- 0x400D00C8 -> 0x3F4010C1 STR                         .
- 0x400D00CC -> 0x3F4011CA STR                         .
- 0x400D00D0 -> 0x3F4012D1 STR                         .
- 0x400D00D4 -> 0x3F4013D2 STR                         .
- 0x400D00D8 -> 0x3F4014C9 STR                                                   
- 0x400D00DC -> 0x3F40154E STR                                          https://g
- 0x400D00E0 -> 0x3F4015D3 STR                                                I'm
- 0x400D00E4 -> 0x3FFC3B28 DRAM/BSS
- 0x400D00E8 -> 0x00002000 IMM 8192
- 0x400D00EC -> 0x3F401658 STR RadioTask
- 0x400D00F0 -> 0x400D236C FN radioTask
- 0x400D00F4 -> 0x4015E3C0 FN FUN_4015e3c0
- 0x400D00F8 -> 0x3FFBDB6C DRAM/BSS
- 0x400D00FC -> 0x3FFC3B24 DRAM/BSS
- 0x400D0100 -> 0x3FFC3B20 DRAM/BSS
- 0x400D0104 -> 0x3FFBDB68 DRAM/BSS
- 0x400D0108 -> 0x3FFC3B2C DRAM/BSS
- 0x400D010C -> 0x3F401662 STR State 1: Bluetooth
- 0x400D0110 -> 0x3F401675 STR bitmap1
- 0x400D0114 -> 0x3F40167D STR State 2: Bluetooth Low Energy
- 0x400D0118 -> 0x3F40169B STR bitmap2
- 0x400D011C -> 0x3F4016A3 STR State 3: WiFi
- 0x400D0120 -> 0x3F4016B1 STR bitmap3
- 0x400D0124 -> 0x3F4016B9 STR State 4: RC
- 0x400D0128 -> 0x3F4016C5 STR bitmap4
- 0x400D012C -> 0x00F42400 
- 0x400D0130 -> 0x3FFC4018 DRAM/BSS
- 0x400D0134 -> 0x3F406B12 STR OK
- 0x400D0138 -> 0x3F40EB56 STR FAIL
- 0x400D013C -> 0x3F4016CD STR State 0: Idle & Status
- 0x400D0140 -> 0x3FFC3B18 DRAM/BSS
- 0x400D0144 -> 0x3FFC3BB0 DRAM/BSS
- 0x400D0148 -> 0x3F4016E4 STR R1=
- 0x400D014C -> 0x00080000 IMM 524288
- 0x400D0150 -> 0x3F4016E8 STR R2=
- 0x400D0154 -> 0x001A0037 IMM 1703991
- 0x400D0158 -> 0x3F4016EC STR USB
- 0x400D015C -> 0x66666667 
- 0x400D0160 -> 0x80000003 
- 0x400D0164 -> 0x3F4016F0 STR Connected
- 0x400D0168 -> 0x3F406DC3 STR .
- 0x400D016C -> 0x4015E7FC FN FUN_4015e7fc
- 0x400D0170 -> 0x4015E79C FN FUN_4015e79c
- 0x400D0174 -> 0x4015EBE4 FN FUN_4015ebe4
- 0x400D0178 -> 0x3FFC3B34 DRAM/BSS
- 0x400D017C -> 0x3FFC3B30 DRAM/BSS
- 0x400D0180 -> 0x3FFBDB78 DRAM/BSS
- 0x400D0184 -> 0x3FFC3B1C DRAM/BSS
- 0x400D0188 -> 0x4015E3C8 FN FUN_4015e3c8
- 0x400D018C -> 0x3FFC3CD4 DRAM/BSS
- 0x400D0190 -> 0x3F4016FA STR SSD1306 allocation failed
- 0x400D0194 -> 0x00010001 IMM 65537
- 0x400D0198 -> 0x3F40082D STR bitmapboot
- 0x400D019C -> 0x3F4023A0 STR 
- 0x400D01A0 -> 0x3F401714 STR by @emensta
- 0x400D01A4 -> 0x3F401675 STR bitmap1
- 0x400D01A8 -> 0x3F402080 STR 
- 0x400D01AC -> 0x3F40169B STR bitmap2
- 0x400D01B0 -> 0x3F401D60 STR 
- 0x400D01B4 -> 0x3F4016B1 STR bitmap3
- 0x400D01B8 -> 0x3F401A40 STR 
- 0x400D01BC -> 0x3F4016C5 STR bitmap4
- 0x400D01C0 -> 0x3F401720 STR 
- 0x400D01C4 -> 0x4015E924 FN FUN_4015e924
- 0x400D01C8 -> 0x00061A80 IMM 400000
- 0x400D01CC -> 0x000186A0 IMM 100000
- 0x400D01D0 -> 0x000088B8 IMM 35000
- 0x400D01D4 -> 0x00989680 
- 0x400D01D8 -> 0x4015E3A0 FN FUN_4015e3a0
- 0x400D01DC -> 0x00001388 IMM 5000
- 0x400D01E0 -> 0x000F4240 IMM 1000000
- 0x400D01E4 -> 0x4015ECA0 FN FUN_4015eca0
- 0x400D01E8 -> 0x3FFC3C1C DRAM/BSS
- 0x400D01EC -> 0x4015E414 FN FUN_4015e414
- 0x400D01F0 -> 0x3F4027B0 STR esp32-
- 0x400D01F4 -> 0x3F4027B7 STR %s%02X%02X%02X
- 0x400D01F8 -> 0x3FFC3C3C DRAM/BSS
- 0x400D01FC -> 0x401514D0 FN FUN_401514d0
- 0x400D0200 -> 0x3FFC3C5C DRAM/BSS
- 0x400D0204 -> 0x3FFC3C38 DRAM/BSS
- 0x400D0208 -> 0x3FFBDEE0 DRAM/BSS
- 0x400D020C -> 0x3FFBDEC4 DRAM/BSS
- 0x400D0210 -> 0x3FFBDEC0 DRAM/BSS
- 0x400D0214 -> 0x3FFBDED4 DRAM/BSS
- 0x400D0218 -> 0x3FFBF698 DRAM/BSS
- 0x400D021C -> 0x3FFC3C2F DRAM/BSS
- 0x400D0220 -> 0x3FFC3C30 DRAM/BSS
- 0x400D0224 -> 0x3FFC3C34 DRAM/BSS
- 0x400D0228 -> 0x400D3944 CODE
- 0x400D022C -> 0x00001000 IMM 4096
- 0x400D0230 -> 0x3F4027C6 STR arduino_events
- 0x400D0234 -> 0x400D44A0 FN FUN_400d44a0
- 0x400D0238 -> 0x401664E4 FN FUN_401664e4
- 0x400D023C -> 0x4016647C FN FUN_4016647c
- 0x400D0240 -> 0x3FFC3C2E DRAM/BSS
- 0x400D0244 -> 0x400E5244 FN FUN_400e5244
- 0x400D0248 -> 0x3FFBDF38 DRAM/BSS
- 0x400D024C -> 0x1F2F3F4F 
- 0x400D0250 -> 0x3F407F3C STR l
- 0x400D0254 -> 0x3FFBDED8 DRAM/BSS
- 0x400D0258 -> 0x3FFC3C2D DRAM/BSS
- 0x400D025C -> 0x3FFC3C2C DRAM/BSS
- 0x400D0260 -> 0x3FFBDB88 DRAM/BSS
- 0x400D0264 -> 0x3FFC3C1D DRAM/BSS
- 0x400D0268 -> 0xFFFFAFFB 
- 0x400D026C -> 0x3F4032E8 STR .
- 0x400D0270 -> 0x00FF0000 
- 0x400D0274 -> 0x0000FF00 IMM 65280
- 0x400D0278 -> 0x4015F4F8 FN FUN_4015f4f8
- 0x400D027C -> 0x4015F4D8 FN FUN_4015f4d8

## Done
