# Display + SPI deep mine

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

## `FUN_400d5220` @ `400d5220`

*(long — see decomp_display_spi/400d5220_FUN_400d5220.c)*

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
  display_clearDisplay(param_1);
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
// ...
```

## `display_clearDisplay` @ `400d51fc`

```c

void display_clearDisplay(int param_1)

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

## `display_display` @ `400d56b4`

*(long — see decomp_display_spi/400d56b4_display_display.c)*

```c

void display_display(int param_1)

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
    digitalWrite(*(undefined1 *)(param_1 + 0x36),0);
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
    digitalWrite(*(undefined1 *)(param_1 + 0x35),1);
    while (uVar3 = uVar3 - 1 & 0xffff, uVar3 != DAT_400d0328) {
      bVar1 = *pbVar4;
      if (*(int *)(param_1 + 0x24) == 0) {
        iVar2 = 8;
        uVar6 = 0x80;
        do {
          digitalWrite(*(undefined1 *)(param_1 + 0x33),bVar1 & uVar6);
          digitalWrite(*(undefined1 *)(param_1 + 0x34),1);
          digitalWrite(*(undefined1 *)(param_1 + 0x34),0);
// ...
```

## `FUN_400d4fd8` @ `400d4fd8`

```c

void FUN_400d4fd8(undefined4 param_1,undefined1 param_2)

{
  (*(code *)PTR_FUN_400d02ec)(param_1,param_2,param_2);
  return;
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

## `FUN_400d5eec` @ `400d5eec`

```c

void FUN_400d5eec(undefined4 param_1)

{
  FUN_400d5ed4(param_1);
  return;
}


```

## `FUN_400d2f0c` @ `400d2f0c`

```c

void FUN_400d2f0c(void)

{
  FUN_400d5014(DAT_400d0144,0x80,0x40,DAT_400d018c,0xffffffff,DAT_400d01c8,DAT_400d01cc);
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
  display_clearDisplay(iVar1);
  *(undefined4 *)(iVar1 + 0x14) = DAT_400d0194;
  display_display(iVar1);
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
  display_clearDisplay(DAT_400d0144);
  iVar3 = 0;
  if (param_2 == '\0') goto LAB_400d2e12;
  iVar3 = FUN_400910b8(param_1,PTR_str_bitmapboot_400d0198);
  if (iVar3 == 0) {
    (*(code *)PTR_FUN_400d01c4)(iVar2,0,0,PTR_bitmap_boot_or_extra_data_400d019c,0x80,0x40,1);
  }
  while( true ) {
    display_display(iVar2);
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

## `FUN_400d2a24` @ `400d2a24`

*(long — see decomp_display_spi/400d2a24_FUN_400d2a24.c)*

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
  display_clearDisplay(DAT_400d0144);
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
// ...
```

- missing 0x400d01c4
## `FUN_4015e924` @ `4015e924`

```c

void FUN_4015e924(int *param_1,short param_2,short param_3,int param_4,short param_5,short param_6,
                 undefined2 param_7)

{
  int iVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  short sVar5;
  uint uVar6;
  
  iVar1 = (int)param_5;
  (**(code **)(*param_1 + 0x1c))(param_1);
  iVar3 = iVar1 + 7;
  if (iVar1 + 7 < 0) {
    iVar3 = iVar1 + 0xe;
  }
  iVar4 = 0;
  sVar5 = 0;
  cVar2 = '\0';
  while( true ) {
    if (param_6 <= sVar5) break;
    for (uVar6 = 0; (int)uVar6 < iVar1; uVar6 = (uint)(short)((short)uVar6 + 1)) {
      cVar2 = cVar2 << 1;
      if ((uVar6 & 7) == 0) {
        cVar2 = *(char *)(param_4 + iVar4 + ((int)uVar6 >> 3));
      }
      if (cVar2 < '\0') {
        (**(code **)(*param_1 + 0x20))
                  (param_1,(int)(short)((short)uVar6 + param_2),(int)(short)(sVar5 + param_3),
                   param_7);
      }
    }
    sVar5 = sVar5 + 1;
    iVar4 = iVar4 + (iVar3 >> 3);
  }
  (**(code **)(*param_1 + 0x34))(param_1);
  return;
}


```

## `FUN_4015e7fc` @ `4015e7fc`

```c

void FUN_4015e7fc(int *param_1,short param_2,short param_3,short param_4,short param_5,
                 undefined2 param_6)

{
  int iVar1;
  int iVar2;
  
  iVar2 = (int)param_3;
  (**(code **)(*param_1 + 0x1c))(param_1);
  iVar1 = (int)param_2;
  (**(code **)(*param_1 + 0x2c))(param_1,iVar1,iVar2,(int)param_4,param_6);
  (**(code **)(*param_1 + 0x2c))
            (param_1,iVar1,(int)(short)(param_5 + -1 + param_3),(int)param_4,param_6);
  (**(code **)(*param_1 + 0x28))(param_1,iVar1,iVar2,(int)param_5,param_6);
  (**(code **)(*param_1 + 0x28))
            (param_1,(int)(short)(param_4 + -1 + param_2),iVar2,(int)param_5,param_6);
  (**(code **)(*param_1 + 0x34))(param_1);
  return;
}


```

## `FUN_4015e79c` @ `4015e79c`

```c

void FUN_4015e79c(int *param_1,short param_2,short param_3,short param_4,short param_5,
                 undefined2 param_6)

{
  int iVar1;
  int iVar2;
  
  iVar1 = (int)param_2;
  (**(code **)(*param_1 + 0x1c))(param_1);
  iVar2 = iVar1 + param_4;
  for (; iVar1 < iVar2; iVar1 = (int)(short)((short)iVar1 + 1)) {
    (**(code **)(*param_1 + 0x28))(param_1,iVar1,(int)param_3,(int)param_5,param_6);
  }
  (**(code **)(*param_1 + 0x34))(param_1);
  return;
}


```

## `FUN_4015ebe4` @ `4015ebe4`

```c

undefined4 FUN_4015ebe4(int *param_1,int *param_2)

{
  undefined4 uVar1;
  int *piVar2;
  uint uVar3;
  
  if ((*(byte *)((int)param_2 + 0xf) & 0x80) == 0) {
    piVar2 = (int *)*param_2;
    uVar3 = 0;
    if (piVar2 != (int *)0x0) {
      uVar3 = param_2[2];
    }
  }
  else {
    uVar3 = (uint)param_2[3] >> 0x18 & 0x7f;
    piVar2 = param_2;
  }
  uVar1 = (**(code **)(*param_1 + 0xc))(param_1,piVar2,uVar3);
  return uVar1;
}


```

## `FUN_400d6d08` @ `400d6d08`

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
    *(undefined4 *)(iVar2 + 0x34) = 0;
    memw();
    *(undefined4 *)(iVar2 + 0x1c) = 0;
    memw();
    *(undefined4 *)(iVar2 + 0x20) = 0;
    memw();
    *(undefined4 *)(iVar2 + 8) = 0;
    memw();
    *(undefined4 *)(iVar2 + 0xc) = 0;
    memw();
    *(undefined4 *)(iVar2 + 0x14) = 0;
    memw();
    *(undefined4 *)(iVar2 + 0x18) = 0;
    memw();
    memw();
    *(uint *)(iVar2 + 0x1c) = *(uint *)(iVar2 + 0x1c) | DAT_400d042c;
    memw();
    memw();
    *(uint *)(iVar2 + 0x1c) = *(uint *)(iVar2 + 0x1c) | DAT_400d0430;
    memw();
    memw();
    *(uint *)(iVar2 + 0x1c) = *(uint *)(iVar2 + 0x1c) | 1;
    memw();
    *(undefined4 *)(iVar2 + 0x80) = 0;
    FUN_40093c38(*(undefined4 *)(PTR_DAT_400d0418 + param_1 * 0xc + 4),0,0);
    FUN_400d6ba8(piVar1,param_3);
    FUN_400d6c30(piVar1,param_4);
    FUN_400d6b80(piVar1,param_2);
    FUN_400d7a38(piVar1,PTR_LAB_400d0414);
  }
  else {
LAB_400d6d19:
    piVar1 = (int *)0x0;
  }
  return piVar1;
}


```

## `FUN_400d7038` @ `400d7038`

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
        }
      }
    } while ((uVar7 != param_1) && (uVar8 = uVar8 & 0x3f, uVar2 = uVar3, uVar8 != 0));
  }
  return uVar3;
}


```

## `FUN_400d680c` @ `400d680c`

```c

void FUN_400d680c(int param_1,char param_2)

{
  byte bVar1;
  undefined4 uVar2;
  
  if (param_1 != 0) {
    if (param_2 < '\0') {
      param_2 = '\x0e';
      if ((*(char *)(param_1 + 8) != '\x02') && (param_2 = '\x12', *(char *)(param_1 + 8) != '\x03')
         ) {
        param_2 = '\x06';
      }
    }
    pinMode((int)param_2,3);
    bVar1 = *(byte *)(param_1 + 8);
    uVar2 = 0;
    if (((1 < bVar1) && (uVar2 = 8, bVar1 != 2)) && (uVar2 = 0, bVar1 == 3)) {
      uVar2 = 0x3f;
    }
    FUN_400d7c40((int)param_2,uVar2,0);
  }
  return;
}


```

## `FUN_400d6860` @ `400d6860`

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
    pinMode((int)param_2,1);
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

## `FUN_400d68cc` @ `400d68cc`

```c

void FUN_400d68cc(int param_1,char param_2)

{
  byte bVar1;
  undefined4 uVar2;
  
  if (param_1 != 0) {
    if (param_2 < '\0') {
      param_2 = '\r';
      if ((*(char *)(param_1 + 8) != '\x02') && (param_2 = '\x17', *(char *)(param_1 + 8) != '\x03')
         ) {
        param_2 = '\b';
      }
    }
    pinMode((int)param_2,3);
    bVar1 = *(byte *)(param_1 + 8);
    uVar2 = 2;
    if (((1 < bVar1) && (uVar2 = 10, bVar1 != 2)) && (uVar2 = 0x41, bVar1 != 3)) {
      uVar2 = 0;
    }
    FUN_400d7c40((int)param_2,uVar2,0);
  }
  return;
}


```

## `FUN_400d6920` @ `400d6920`

```c

void FUN_400d6920(int param_1,char param_2)

{
  if (param_1 != 0) {
    if (param_2 < '\0') {
      param_2 = '\x0e';
      if ((*(char *)(param_1 + 8) != '\x02') && (param_2 = '\x12', *(char *)(param_1 + 8) != '\x03')
         ) {
        param_2 = '\x06';
      }
    }
    FUN_400d7c58((int)param_2,0);
    pinMode((int)param_2,1);
  }
  return;
}


```

## `FUN_400d6958` @ `400d6958`

```c

void FUN_400d6958(int param_1,char param_2)

{
  byte bVar1;
  undefined4 uVar2;
  
  if (param_1 == 0) {
    return;
  }
  bVar1 = *(byte *)(param_1 + 8);
  if (param_2 < '\0') {
    param_2 = '\f';
    uVar2 = 9;
    if (bVar1 == 2) goto LAB_400d697a;
    param_2 = '\x13';
    uVar2 = 0x40;
    if (bVar1 == 3) goto LAB_400d697a;
    param_2 = '\a';
    uVar2 = 1;
    if (bVar1 < 2) goto LAB_400d697a;
  }
  else {
    uVar2 = 1;
    if ((bVar1 < 2) || (uVar2 = 9, bVar1 == 2)) goto LAB_400d697a;
  }
  uVar2 = 0x40;
  if (bVar1 != 3) {
    uVar2 = 0;
  }
LAB_400d697a:
  FUN_400d7c84(uVar2,0);
  pinMode((int)param_2,1);
  return;
}


```

## `FUN_400d69b0` @ `400d69b0`

```c

void FUN_400d69b0(int param_1,char param_2)

{
  if (param_1 != 0) {
    if (param_2 < '\0') {
      param_2 = '\r';
      if ((*(char *)(param_1 + 8) != '\x02') && (param_2 = '\x17', *(char *)(param_1 + 8) != '\x03')
         ) {
        param_2 = '\b';
      }
    }
    FUN_400d7c58((int)param_2,0);
    pinMode((int)param_2,1);
  }
  return;
}


```

## `FUN_400d6a5c` @ `400d6a5c`

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
  pinMode((int)param_3,3);
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

## `FUN_400d69e8` @ `400d69e8`

```c

void FUN_400d69e8(int param_1,char param_2)

{
  if (param_1 != 0) {
    if (param_2 < '\0') {
      param_2 = '\x0f';
      if ((*(char *)(param_1 + 8) != '\x02') && (param_2 = '\x05', *(char *)(param_1 + 8) != '\x03')
         ) {
        param_2 = '\v';
      }
    }
    FUN_400d7c58((int)param_2,0);
    pinMode((int)param_2,1);
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

## `FUN_400d5ac4` @ `400d5ac4`

*(long — see decomp_display_spi/400d5ac4_FUN_400d5ac4.c)*

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
// ...
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

## `FUN_400d380c` @ `400d380c`

```c

void FUN_400d380c(undefined1 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  iVar1 = digitalRead(*param_1);
  *(int *)(param_1 + 0x1c) = iVar1;
  if (*(int *)(param_1 + 0x18) != iVar1) {
    uVar2 = millis();
    *(undefined4 *)(param_1 + 0x20) = uVar2;
    *(undefined4 *)(param_1 + 0x18) = *(undefined4 *)(param_1 + 0x1c);
  }
  iVar1 = millis();
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

## `FUN_400d37d8` @ `400d37d8`

```c

void FUN_400d37d8(uint *param_1,uint param_2)

{
  uint uVar1;
  
  *param_1 = param_2;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  pinMode(param_2 & 0xff,5);
  uVar1 = digitalRead((char)*param_1);
  param_1[4] = uVar1;
  uVar1 = digitalRead((char)*param_1);
  param_1[5] = uVar1;
  uVar1 = digitalRead((char)*param_1);
  param_1[6] = uVar1;
  param_1[8] = 0;
  return;
}


```

## `nrf_writeCmd` @ `400d2f90`

```c

void nrf_writeCmd(undefined4 *param_1,undefined1 param_2,undefined1 *param_3,char param_4)

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

## `nrf_writeBytes` @ `400d2ff8`

```c

void nrf_writeBytes(undefined4 *param_1,byte param_2,undefined1 *param_3,char param_4)

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

void nrf_writeRegister(undefined4 *param_1,byte param_2,undefined1 param_3)

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

## `nrf_readRegister` @ `400d2fcc`

```c

undefined4 nrf_readRegister(undefined4 *param_1,undefined1 param_2)

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

## `nrf_csnLow` @ `400d2f60`

```c

void nrf_csnLow(undefined4 *param_1)

{
  FUN_400d3730(*param_1,param_1[2],1);
  nrf_csn(param_1,0);
  return;
}


```

## `nrf_csnHigh` @ `400d2f7c`

```c

void nrf_csnHigh(undefined4 *param_1)

{
  nrf_csn(param_1,1);
  FUN_400d3778(*param_1);
  return;
}


```

## Callers of drawBitmap ptr 0x4015E924

- 400d52bb in FUN_400d5220
- 400d2df1 in FUN_400d2dac
- 400d2e89 in FUN_400d2dac
- 400d01c4 in ?

Done
