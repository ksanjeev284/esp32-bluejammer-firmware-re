# Ghidra Headless Findings

Program: `seg2_IROM_0x400D0020.bin`
Language: `Xtensa:LE:32:default`
Image base: `00000000`

## Memory blocks
- **DROM** 3f400020 – 3f41cfcf size=118704 perms=R--
- **DRAM1** 3ffbdb60 – 3ffc0b9f size=12352 perms=RW-
- **DRAM2** 3ffc0ba0 – 3ffc3b17 size=12152 perms=RW-
- **IRAM** 40080000 – 4009a277 size=107128 perms=R-X
- **IROM** 400d0020 – 4016907f size=626784 perms=R-X

## Functions (4244)
Full list: `functions.txt`

### First 40 functions by address
- `400812c4` FUN_400812c4
- `400816bc` FUN_400816bc
- `40081710` FUN_40081710
- `40081768` FUN_40081768
- `40081814` FUN_40081814
- `400819ec` FUN_400819ec
- `40081a0c` FUN_40081a0c
- `40081a38` FUN_40081a38
- `40081a60` FUN_40081a60
- `40081ae0` FUN_40081ae0
- `40081af8` FUN_40081af8
- `40081b14` FUN_40081b14
- `40081b84` FUN_40081b84
- `40081dac` FUN_40081dac
- `40081e1c` FUN_40081e1c
- `40081eb4` FUN_40081eb4
- `40081f08` FUN_40081f08
- `40081f70` FUN_40081f70
- `40081f80` FUN_40081f80
- `40081fc4` FUN_40081fc4
- `40082004` FUN_40082004
- `40082078` FUN_40082078
- `400820e0` FUN_400820e0
- `40082140` FUN_40082140
- `400821a0` FUN_400821a0
- `40082298` FUN_40082298
- `400824a4` FUN_400824a4
- `400825b4` FUN_400825b4
- `400826f4` FUN_400826f4
- `4008271c` FUN_4008271c
- `40082898` FUN_40082898
- `400828b0` FUN_400828b0
- `400828bc` FUN_400828bc
- `40082904` FUN_40082904
- `40082914` FUN_40082914
- `40082978` FUN_40082978
- `40082988` FUN_40082988
- `40082998` FUN_40082998
- `400829a4` FUN_400829a4
- `400829c0` FUN_400829c0

## Cross-references to application anchors

### Xrefs to HSPI_SUCCESS @ 0x3F4002C4
  from 400d003c  (<no func>)  type=DATA

### Xrefs to HSPI_FAIL @ 0x3F40044A
  from 400d0050  (<no func>)  type=DATA

### Xrefs to VSPI_SUCCESS @ 0x3F400608
  from 400d0064  (<no func>)  type=DATA

### Xrefs to VSPI_FAIL @ 0x3F400793
  from 400d2553  (<no func>)  type=PARAM
  from 400d0078  (<no func>)  type=DATA

### Xrefs to State1 @ 0x3F401662
  from 400d28eb  (FUN_400d28d8 @ 400d28d8)  type=PARAM
  from 400d010c  (<no func>)  type=DATA

### Xrefs to State2 @ 0x3F40167D
  from 400d2933  (FUN_400d2920 @ 400d2920)  type=PARAM
  from 400d0114  (<no func>)  type=DATA

### Xrefs to State3 @ 0x3F4016A3
  from 400d297b  (FUN_400d2968 @ 400d2968)  type=PARAM
  from 400d011c  (<no func>)  type=DATA

### Xrefs to State4 @ 0x3F4016B9
  from 400d29c3  (FUN_400d29b0 @ 400d29b0)  type=PARAM
  from 400d0124  (<no func>)  type=DATA

### Xrefs to State0 @ 0x3F4016CD
  from 400d2a47  (FUN_400d2a24 @ 400d2a24)  type=PARAM
  from 400d2a5f  (FUN_400d2a24 @ 400d2a24)  type=PARAM
  from 400d013c  (<no func>)  type=DATA

### Xrefs to SSD1306_fail @ 0x3F4016FA
  from 400d0190  (<no func>)  type=DATA

### Xrefs to by_emensta @ 0x3F401714
  from 400d01a0  (<no func>)  type=DATA

### Xrefs to Firmware_banner @ 0x3F400E16
  from 400d00bc  (<no func>)  type=DATA

### Xrefs to RadioTask_str @ 0x3F401658
  from 400d00ec  (<no func>)  type=DATA

### Xrefs to bitmap1_data @ 0x3F402080
  from 400d2df9  (FUN_400d2dac @ 400d2dac)  type=PARAM
  from 400d01a8  (<no func>)  type=DATA

### Xrefs to bitmap2_data @ 0x3F401D60
  from 400d2e89  (FUN_400d2dac @ 400d2dac)  type=PARAM
  from 400d01b0  (<no func>)  type=DATA

### Xrefs to bitmap3_data @ 0x3F401A40
  from 400d2e89  (FUN_400d2dac @ 400d2dac)  type=PARAM
  from 400d01b8  (<no func>)  type=DATA

### Xrefs to bitmap4_data @ 0x3F401720
  from 400d2e89  (FUN_400d2dac @ 400d2dac)  type=PARAM
  from 400d01c0  (<no func>)  type=DATA

### Xrefs to table_state_strings @ 0x400D010C
  from 400d28e3  (FUN_400d28d8 @ 400d28d8)  type=READ

### Xrefs to radioTask @ 0x400D236C
  from 400d00f0  (<no func>)  type=DATA
Created function radioTask: radioTask

## Decompilation of interesting functions

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
  FUN_400d6724(2);
  uVar6 = (*(code *)PTR_FUN_400d0084)(0x20);
  FUN_400d35d0(uVar6,2);
  FUN_400d35fc(uVar6,0xe,0xc,0xd,0xf);
  FUN_400d6724(5);
  uVar7 = (*(code *)PTR_FUN_400d0084)(0x20);
  FUN_400d35d0(uVar7,3);
  FUN_400d35fc(uVar7,0x12,0x13,0x17,0x15);
  FUN_400d6724(5);
  uVar2 = DAT_400d0024;
  iVar8 = FUN_400d3448(DAT_400d0024,uVar6);
  puVar3 = PTR_s__________________________________400d002c;
  uVar6 = DAT_400d0028;
  if (iVar8 == 0) {
    FUN_400d5d1c(DAT_400d0028);
    FUN_400d5d30(uVar6,puVar3);
    FUN_400d5d1c(uVar6);
    FUN_400d5d30(uVar6,PTR_DAT_400d0044);
    FUN_400d5d30(uVar6,PTR_DAT_400d0048);
    FUN_400d5d30(uVar6,PTR_DAT_400d004c);
    FUN_400d5d1c(uVar6);
    FUN_400d5d30(uVar6,PTR_str_HSPI_FAIL_400d0050);
  }
  else {
    FUN_400d5d1c(DAT_400d0028);
    FUN_400d5d30(uVar6,puVar3);
    FUN_400d5d1c(uVar6);
    FUN_400d5d30(uVar6,PTR_DAT_400d0030);
    FUN_400d5d30(uVar6,PTR_DAT_400d0034);
    FUN_400d5d30(uVar6,PTR_DAT_400d0038);
    FUN_400d5d1c(uVar6);
    FUN_400d5d30(uVar6,PTR_str_HSPI_SUCCESS_400d003c);
    FUN_400d32c4(uVar2,0);
    FUN_400d3180(uVar2);
    FUN_400d34b0(uVar2,0);
    FUN_400d32f4(uVar2,3,1);
    FUN_400d3328(uVar2,1);
    FUN_400d3460(uVar2,0);
    FUN_400d34d8(uVar2,3,*PTR_DAT_400d0040);
  }
  uVar4 = DAT_400d0054;
  iVar8 = FUN_400d3448(DAT_400d0054,uVar7);
  if (iVar8 == 0) {
    FUN_400d5d1c(uVar6);
    FUN_400d5d30(uVar6,puVar3);
    FUN_400d5d1c(uVar6);
    FUN_400d5d30(uVar6,PTR_DAT_400d006c);
    FUN_400d5d30(uVar6,PTR_DAT_400d0070);
    FUN_400d5d30(uVar6,PTR_DAT_400d0074);
    FUN_400d5d1c(uVar6);
    FUN_400d5d30(uVar6,PTR_str_VSPI_FAIL_400d0078);
    pcVar1 = DAT_400d007c;
  }
  else {
    FUN_400d5d1c(uVar6);
    FUN_400d5d30(uVar6,puVar3);
    FUN_400d5d1c(uVar6);
    FUN_400d5d30(uVar6,PTR_DAT_400d0058);
    FUN_400d5d30(uVar6,PTR_DAT_400d005c);
    FUN_400d5d30(uVar6,PTR_DAT_400d0060);
    FUN_400d5d1c(uVar6);
    FUN_400d5d30(uVar6,PTR_str_VSPI_SUCCESS_400d0064);
    FUN_400d32c4(uVar4,0);
    FUN_400d3180(uVar4);
    FUN_400d34b0(uVar4,0);
    FUN_400d32f4(uVar4,3,1);
    FUN_400d3328(uVar4,1);
    FUN_400d3460(uVar4,0);
    FUN_400d34d8(uVar4,3,*PTR_DAT_400d0068);
    pcVar1 = DAT_400d007c;
  }
  do {
    iVar8 = 100;
    do {
      memw();
      if (*pcVar1 != '\0') {
        FUN_400d3590(uVar2);
        FUN_400d3590(uVar4);
        FUN_400d31d8(uVar2);
        FUN_400d31d8(uVar4);
        while (memw(), *pcVar1 != '\0') {
          FUN_40095724(10);
        }
        FUN_400d31fc(uVar2);
        FUN_400d31fc(uVar4);
        FUN_400d34d8(uVar2,3,*PTR_DAT_400d0040);
        FUN_400d34d8(uVar4,3,*PTR_DAT_400d0068);
      }
      memw();
      iVar9 = *(int *)PTR_DAT_400d0080;
      if (iVar9 == 2) {
        uVar5 = FUN_400d5e80(0x27);
        FUN_400d30d8(uVar2,uVar5);
        uVar6 = 0x27;
LAB_400d26b7:
        uVar5 = FUN_400d5e80(uVar6);
        FUN_400d30d8(uVar4,uVar5);
      }
      else {
        if (2 < iVar9) {
          if (iVar9 == 3) {
            uVar5 = FUN_400d5e80(0xe);
            FUN_400d30d8(uVar2,uVar5);
            uVar6 = 0xe;
          }
// ... truncated, see decomp/400d236c_radioTask.c
```
Full: `decomp/400d236c_radioTask.c`

### `FUN_400d28d8` @ `400d28d8`
```c

void FUN_400d28d8(void)

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
Full: `decomp/400d28d8_FUN_400d28d8.c`

### `FUN_400d2920` @ `400d2920`
```c

void FUN_400d2920(void)

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
    FUN_400d6214(0x1b);
    *(undefined4 *)PTR_DAT_400d0104 = 2;
  }
  FUN_400d2868();
  return;
}

```
Full: `decomp/400d2920_FUN_400d2920.c`

### `FUN_400d2968` @ `400d2968`
```c

void FUN_400d2968(void)

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
    FUN_400d6214(0x1b);
    *(undefined4 *)PTR_DAT_400d0104 = 3;
  }
  FUN_400d2868();
  return;
}

```
Full: `decomp/400d2968_FUN_400d2968.c`

### `FUN_400d29b0` @ `400d29b0`
```c

void FUN_400d29b0(void)

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
    FUN_400d6214(0x1b);
    *(undefined4 *)PTR_DAT_400d0104 = 4;
  }
  FUN_400d2868();
  return;
}

```
Full: `decomp/400d29b0_FUN_400d29b0.c`

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
    FUN_400d5d30(DAT_400d0028,PTR_str_State0_Idle_400d013c);
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
  iVar3 = FUN_400d3120(DAT_400d0024);
  puVar6 = PTR_s_OK_3f406b01_0x11_400d0134;
  if (iVar3 == 0) {
    puVar6 = PTR_s_FAIL_3f40eb3c_0x1a_400d0138;
  }
  FUN_400d5d08(iVar4,puVar6);
  puVar6 = PTR_DAT_400d0150;
  *(undefined4 *)(iVar4 + 0x10) = DAT_400d014c;
  FUN_400d5d08(iVar4,puVar6);
  iVar3 = FUN_400d3120(DAT_400d0054);
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
    if (iStack_24 == iVar4) break;
    FUN_40082e5c();
    FUN_400d5eec(aiStack_34);
    (*(code *)PTR_FUN_400d008c)(iVar4);
LAB_400d2bf0:
    uVar5 = uStack_28 >> 0x18 & 0x7f;
  }
  return;
}

```
Full: `decomp/400d2a24_FUN_400d2a24.c`

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
Full: `decomp/400d2dac_FUN_400d2dac.c`

## Disassembly snippet near radioTask (0x400D236C)
```
400d236c  entry a1,0x20
400d236f  l32r a10,0x400d0020
400d2372  mov a1,a1
400d2375  call8 0x400d36e4
400d2378  movi.n a10,0x2
400d237a  mov a1,a1
400d237d  call8 0x400d6724
400d2380  movi.n a10,0x20
400d2382  l32r a8,0x400d0084
400d2385  callx8 a8
400d2388  movi.n a11,0x2
400d238a  mov.n a4,a10
400d238c  mov a1,a1
400d238f  call8 0x400d35d0
400d2392  movi.n a11,0xe
400d2394  movi.n a14,0xf
400d2396  movi.n a13,0xd
400d2398  movi.n a12,0xc
400d239a  mov.n a10,a4
400d239c  mov a1,a1
400d239f  call8 0x400d35fc
400d23a2  movi.n a10,0x5
400d23a4  mov a1,a1
400d23a7  call8 0x400d6724
400d23aa  movi.n a10,0x20
400d23ac  l32r a8,0x400d0084
400d23af  callx8 a8
400d23b2  movi.n a11,0x3
400d23b4  mov.n a5,a10
400d23b6  mov a1,a1
400d23b9  call8 0x400d35d0
400d23bc  movi.n a14,0x15
400d23be  movi.n a13,0x17
400d23c0  movi.n a12,0x13
400d23c2  movi.n a11,0x12
400d23c4  mov.n a10,a5
400d23c6  mov a1,a1
400d23c9  call8 0x400d35fc
400d23cc  movi.n a10,0x5
400d23ce  mov a1,a1
```

## User labels
- `3f4002c4` str_HSPI_SUCCESS
- `3f40044a` str_HSPI_FAIL
- `3f400608` str_VSPI_SUCCESS
- `3f400793` str_VSPI_FAIL
- `3f40082d` str_bitmapboot
- `3f400e16` str_Firmware_Banner
- `3f4014c9` str_Educational
- `3f40154e` str_GitHub_URL
- `3f4015d3` str_Disclaimer
- `3f401658` str_RadioTask
- `3f401662` str_State1_Bluetooth
- `3f401675` str_bitmap1
- `3f40167d` str_State2_BLE
- `3f40169b` str_bitmap2
- `3f4016a3` str_State3_WiFi
- `3f4016b1` str_bitmap3
- `3f4016b9` str_State4_RC
- `3f4016c5` str_bitmap4
- `3f4016cd` str_State0_Idle
- `3f4016f0` str_Connected
- `3f4016fa` str_SSD1306_alloc_failed
- `3f401714` str_by_emensta
- `3f401720` bitmap4_data
- `3f401a40` bitmap3_data
- `3f401d60` bitmap2_data
- `3f402080` bitmap1_data
- `3f4023a0` bitmap_boot_or_extra_data
- `3f403649` str_loopTask
- `40082f0c` ESP32_IMAGE_ENTRY
- `400d00ec` ptr_RadioTask_name
- `400d00f0` ptr_radioTask_fn
- `400d010c` table_state_strings
- `400d01a4` table_bitmap_refs
- `400d236c` radioTask
