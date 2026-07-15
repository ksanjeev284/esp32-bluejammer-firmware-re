# Largest / remaining decompilations

## `FUN_400d5220` @ `400d5220` size~619

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
  (*(code *)PTR_FUN_400d01c4)(param_1,iVar2 >> 1,iVar3 >> 1,puVar4,uVar5,uVar6,1);
  *(undefined1 *)(param_1 + 0x31) = param_2;
  if (*(int *)(param_1 + 0x28) == 0) {
    pinMode(*(undefined1 *)(param_1 + 0x35),3);
    pinMode(*(undefined1 *)(param_1 + 0x36),3);
    digitalWrite(*(undefined1 *)(param_1 + 0x36),1);
    if (*(int *)(param_1 + 0x24) == 0) {
      pinMode(*(undefined1 *)(param_1 + 0x33),3);
      pinMode(*(undefined1 *)(param_1 + 0x34),3);
      digitalWrite(*(undefined1 *)(param_1 + 0x34),0);
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
    pinMode((int)*(char *)(param_1 + 0x37),3);
    digitalWrite(*(undefined1 *)(param_1 + 0x37),1);
    delay_ms(1);
    digitalWrite(*(undefined1 *)(param_1 + 0x37),0);
    delay_ms(10);
    digitalWrite(*(undefined1 *)(param_1 + 0x37),1);
  }
  if (*(int *)(param_1 + 0x28) == 0) {
    if (*(int *)(param_1 + 0x24) != 0) {
      FUN_400d3730(*(int *)(param_1 + 0x24),*(undefined4 *)(param_1 + 0x44),
                   *(undefined4 *)(param_1 + 0x48));
    }
    digitalWrite(*(undefined1 *)(param_1 + 0x36),0);
  }
  else {
// truncated — full in decomp_largest/
```

## `FUN_400d4bac` @ `400d4bac` size~773

```c

void FUN_400d4bac(int *param_1,short param_2,short param_3,uint param_4,short param_5,short param_6,
                 byte param_7,byte param_8)

{
  byte bVar1;
  ushort uVar2;
  ushort uVar3;
  char cVar4;
  char cVar5;
  ushort uVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  ushort uVar10;
  ushort *puVar11;
  char cVar12;
  ushort uVar13;
  int *piVar14;
  uint uVar15;
  byte *pbVar16;
  char cVar17;
  ushort uVar18;
  int iVar19;
  code *pcVar20;
  short sVar21;
  short sVar22;
  uint uStack_5c;
  short sStack_58;
  short sStack_48;
  uint uStack_44;
  
  iVar8 = (int)param_3;
  piVar14 = (int *)param_1[8];
  param_4 = param_4 & 0xff;
  uVar9 = (uint)param_7;
  uVar7 = (uint)param_8;
  if (piVar14 == (int *)0x0) {
    if ((int)(short)param_1[3] <= (int)param_2) {
      return;
    }
    if (*(short *)((int)param_1 + 0xe) <= iVar8) {
      return;
    }
    if ((int)(uVar9 * 6 + (int)param_2) < 1) {
      return;
    }
    if ((int)(uVar7 * 8 + iVar8) < 1) {
      return;
    }
    if (((char)param_1[7] != '\x01') && (0xaf < param_4)) {
      param_4 = param_4 + 1 & 0xff;
    }
    (**(code **)(*param_1 + 0x1c))(param_1);
    cVar12 = '\0';
    cVar5 = '\x05';
    do {
      uStack_44 = (uint)(byte)PTR_DAT_400d02e8[(int)cVar12 + param_4 * 5];
      cVar17 = '\b';
      cVar4 = '\0';
      do {
        iVar19 = *param_1;
        if ((uStack_44 & 1) == 0) {
          if (param_5 != param_6) {
            if ((uVar9 != 1) || (uVar7 != 1)) {
              sVar21 = (ushort)param_8 * (short)cVar4;
              pcVar20 = *(code **)(iVar19 + 0x24);
              sVar22 = param_6;
              goto LAB_400d4d16;
            }
            pcVar20 = *(code **)(iVar19 + 0x20);
            sVar21 = param_6;
            goto LAB_400d4c99;
          }
        }
        else if ((uVar9 == 1) && (uVar7 == 1)) {
          pcVar20 = *(code **)(iVar19 + 0x20);
          sVar21 = param_5;
LAB_400d4c99:
          (*pcVar20)(param_1,(int)(short)(cVar12 + param_2),(int)(short)(cVar4 + param_3),sVar21);
// truncated — full in decomp_largest/
```

## `FUN_400d41b4` @ `400d41b4` size~734

```c

void FUN_400d41b4(int *param_1)

{
  int *piVar1;
  int *piVar2;
  byte bVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  int aiStack_188 [45];
  int iStack_d4;
  undefined1 auStack_d0 [4];
  code *pcStack_cc;
  undefined1 auStack_c8 [8];
  int iStack_c0;
  code *pcStack_bc;
  code *pcStack_b8;
  int iStack_b4;
  undefined1 auStack_b0 [140];
  int iStack_24;
  
  piVar1 = DAT_400d0130;
  memw();
  iStack_24 = *DAT_400d0130;
  memw();
  if (param_1 == (int *)0x0) goto LAB_400d446d;
  iVar5 = *param_1;
  if (iVar5 == 1) {
    FUN_400d4840();
  }
  else if (iVar5 == 2) {
    FUN_400d4528(6);
    FUN_400d3e08(8);
    FUN_40126dd0(*(undefined4 *)PTR_DAT_400d0288);
  }
  else {
    if (iVar5 == 3) {
      FUN_400d4528(0xff);
      uVar6 = 0x78;
      goto LAB_400d426c;
    }
    if (iVar5 == 4) {
      FUN_400d4528(0);
      uVar6 = 0x10;
    }
    else {
      if (iVar5 == 5) {
        bVar3 = *(byte *)((int)param_1 + 0x2b);
        if (bVar3 == 0) {
          bVar3 = 1;
LAB_400d42b2:
          uVar6 = 5;
          if ((bVar3 & 0xfb) == 200) goto LAB_400d42c5;
          if (bVar3 != 2) {
            uVar6 = 6;
            goto LAB_400d42c5;
          }
        }
        else {
          uVar6 = 1;
          if ((bVar3 != 0xc9) && ((bVar3 != 0xca || (uVar6 = 4, *PTR_DAT_400d028c != '\0'))))
          goto LAB_400d42b2;
LAB_400d42c5:
          FUN_400d4528(uVar6);
        }
        FUN_400d3e20(0x70);
        uVar6 = DAT_400d01e8;
        if (bVar3 != 8) {
          if (*PTR_DAT_400d028c == '\0') {
            iVar5 = FUN_400d4834(DAT_400d01e8);
            if ((iVar5 == 0) || (iVar5 = (*(code *)PTR_FUN_400d0298)(bVar3), iVar5 == 0)) {
              if (bVar3 == 0xcb) {
                FUN_400d4528(4);
              }
              goto LAB_400d41d4;
            }
          }
          else {
            *PTR_DAT_400d028c = 0;
// truncated — full in decomp_largest/
```

## `FUN_400d3f74` @ `400d3f74` size~489

```c

int FUN_400d3f74(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  undefined4 uStack_44;
  undefined *puStack_40;
  undefined4 uStack_3c;
  uint uStack_38;
  uint uStack_34;
  uint uStack_30;
  undefined1 auStack_2c [4];
  uint uStack_28;
  uint uStack_24;
  
  uStack_38 = *(uint *)(param_2 + 4);
  uStack_30 = *(uint *)(param_3 + 4);
  uVar4 = *(undefined4 *)(DAT_400d0200 + param_1 * 4);
  uStack_34 = *(uint *)(param_4 + 4);
  uStack_44 = 0;
  if (param_1 == 1) {
    iVar2 = (*(code *)PTR_FUN_400d027c)(uVar4,&uStack_44);
    if ((iVar2 == 0) &&
       (((iVar2 = FUN_400e4ee0(uVar4), iVar2 == 0 || (iVar2 + DAT_400d0268 == 0)) &&
        (iVar2 = FUN_400e520c(uVar4,&uStack_38), iVar2 == 0)))) {
      auStack_2c[0] = 1;
      puStack_40 = PTR_PTR_400d026c;
      uStack_3c = *(undefined4 *)(param_4 + 4);
      cVar1 = (*(code *)PTR_FUN_400d0280)(&puStack_40);
      if ((byte)(cVar1 - 0x18U) < 5) {
        uVar5 = uStack_34 >> 0x18 | uStack_34 << 0x18 | uStack_34 << 8 & DAT_400d0270 |
                uStack_34 >> 8 & DAT_400d0274;
        uVar3 = *(uint *)(param_5 + 4);
        uStack_28 = uVar3 >> 0x18 | uVar3 << 0x18 | uVar3 << 8 & DAT_400d0270 |
                    uVar3 >> 8 & DAT_400d0274;
        uVar3 = uStack_38 >> 0x18 | uStack_38 << 0x18 | uStack_38 << 8 & DAT_400d0270 |
                uStack_38 >> 8 & DAT_400d0274;
        if (uStack_28 == 0) {
          uStack_28 = uVar3 + 1;
        }
        uStack_24 = uStack_28 + 10;
        if (((uStack_28 ^ uVar3) & uVar5) == 0) {
          if (-uVar5 - 0xb <= ((uVar5 ^ 0xffffffff) & uStack_28)) {
            uStack_24 = uStack_28 & uVar5;
            uStack_28 = uStack_24 + 1;
            uStack_24 = uStack_24 + 0xb;
          }
          if (((uVar3 < uStack_28) || (uStack_24 < uVar3)) &&
             ((uVar6 = uStack_30 >> 0x18 | uStack_30 << 0x18 | uStack_30 << 8 & DAT_400d0270 |
                       uStack_30 >> 8 & DAT_400d0274, ((uVar3 ^ uVar6) & uVar5) != 0 ||
              ((uVar6 < uStack_28 || (uStack_24 < uVar6)))))) {
            uStack_28 = uStack_28 >> 0x18 | uStack_28 << 0x18 | uStack_28 << 8 & DAT_400d0270 |
                        uStack_28 >> 8 & DAT_400d0274;
            uStack_24 = uStack_24 >> 0x18 | uStack_24 << 0x18 | uStack_24 << 8 & DAT_400d0270 |
                        uStack_24 >> 8 & DAT_400d0274;
            iVar2 = FUN_400e5220(uVar4,1,1,&uStack_34,4);
            if (iVar2 != 0) {
              return iVar2;
            }
            iVar2 = FUN_400e5220(uVar4,1,0x32,auStack_2c,0xc);
            if (iVar2 != 0) {
              return iVar2;
            }
            iVar2 = FUN_400e4ecc(uVar4);
            return iVar2;
          }
        }
      }
      iVar2 = -1;
    }
  }
  else {
    iVar2 = (*(code *)PTR_FUN_400d0278)();
    if (((iVar2 == 0) &&
        (((iVar2 = FUN_400e4ea4(uVar4), iVar2 == 0 || (iVar2 + DAT_400d0268 == 0)) &&
// truncated — full in decomp_largest/
```

## `FUN_400d3b94` @ `400d3b94` size~334

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
       (((iVar3 = (*(code *)PTR_FUN_400d023c)(*(undefined4 *)PTR_PTR_400d020c,0xffffffff,puVar2,0,0)
         , iVar3 == 0 &&
         (iVar3 = (*(code *)PTR_FUN_400d023c)(*(undefined4 *)PTR_PTR_400d0214,0xffffffff,puVar2,0,0)
         , iVar3 == 0)) &&
        (iVar3 = (*(code *)PTR_FUN_400d023c)(*(undefined4 *)PTR_PTR_400d0210,0xffffffff,puVar2,0,0),
        iVar3 == 0)))) {
      iVar3 = (*(code *)PTR_FUN_400d023c)(*(undefined4 *)PTR_PTR_400d0218,0xffffffff,puVar2,0,0);
      puVar7 = (undefined4 *)(uint)(iVar3 == 0);
    }
  }
// truncated — full in decomp_largest/
```

## `FUN_400d5490` @ `400d5490` size~331

```c

void FUN_400d5490(int param_1,short param_2,short param_3,short param_4,short param_5)

{
  int iVar1;
  byte *pbVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  byte bVar6;
  
  iVar1 = (int)param_2;
  uVar3 = (uint)param_3;
  if (iVar1 < 0) {
    return;
  }
  if (*(short *)(param_1 + 8) <= iVar1) {
    return;
  }
  if ((int)uVar3 < 0) {
    param_4 = param_4 + param_3;
    uVar3 = 0;
  }
  uVar4 = (uint)param_4;
  if ((int)*(short *)(param_1 + 10) < (int)(uVar3 + uVar4)) {
    uVar4 = (uint)(short)(*(short *)(param_1 + 10) - (short)uVar3);
  }
  if ((int)uVar4 < 1) {
    return;
  }
  uVar4 = uVar4 & 0xff;
  pbVar2 = (byte *)(*(int *)(param_1 + 0x2c) +
                   (int)(short)((uVar3 & 0xff) >> 3) * (int)*(short *)(param_1 + 8) + iVar1);
  uVar5 = 0;
  if ((uVar3 & 7) == 0) goto LAB_400d5531;
  uVar5 = 8 - (uVar3 & 7) & 0xff;
  bVar6 = PTR_DAT_400d0318[uVar5];
  if (uVar4 < uVar5) {
    bVar6 = (byte)(0xff >> (uVar5 - uVar4 & 0x1f)) & bVar6;
    if (param_5 == 1) goto LAB_400d5520;
    if (param_5 == 0) goto LAB_400d5573;
    if (param_5 != 2) {
      return;
    }
LAB_400d5515:
    bVar6 = bVar6 ^ *pbVar2;
LAB_400d5526:
    *pbVar2 = bVar6;
    if (uVar4 < uVar5) {
      return;
    }
  }
  else {
    if (param_5 == 1) {
LAB_400d5520:
      bVar6 = bVar6 | *pbVar2;
      goto LAB_400d5526;
    }
    if (param_5 == 0) {
LAB_400d5573:
      bVar6 = (bVar6 ^ 0xff) & *pbVar2;
      goto LAB_400d5526;
    }
    if (param_5 == 2) goto LAB_400d5515;
  }
  pbVar2 = pbVar2 + *(short *)(param_1 + 8);
LAB_400d5531:
  uVar3 = uVar4 - uVar5 & 0xff;
  if (7 < uVar3) {
    if (param_5 == 2) {
      iVar1 = (uVar3 - 8 >> 3 & 0x1f) + 1;
      do {
        *pbVar2 = *pbVar2 ^ 0xff;
        pbVar2 = pbVar2 + *(short *)(param_1 + 8);
        iVar1 = iVar1 + -1;
      } while (iVar1 != 0);
    }
    else {
      iVar1 = (uVar3 - 8 >> 3 & 0x1f) + 1;
      do {
// truncated — full in decomp_largest/
```

## `FUN_400d5ac4` @ `400d5ac4` size~385

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
    iVar1 = millis();
    while (iVar3 = millis(), (uint)(iVar3 - iVar1) < param_7) {
      iVar3 = FUN_400d78c8(*(undefined4 *)(param_1 + 0x14));
      if (iVar3 != 0) goto LAB_400d5bae;
      FUN_400d66dc();
    }
    iVar3 = 0;
// truncated — full in decomp_largest/
```

## `FUN_400d6d08` @ `400d6d08` size~370

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
// truncated — full in decomp_largest/
```

## `FUN_400d71d0` @ `400d71d0` size~360

```c

void FUN_400d71d0(undefined4 *param_1,char param_2,char param_3,char param_4,char param_5)

{
  int iVar1;
  uint *puVar2;
  
  if (param_1 != (undefined4 *)0x0) {
    do {
      iVar1 = FUN_40094190(*param_1,0xffffffff);
    } while (iVar1 != 1);
    iVar1 = (int)param_3;
    if (-1 < iVar1) {
      puVar2 = *(uint **)(PTR_DAT_400d0468 + iVar1 * 4);
      if ((uint)((int)puVar2 + DAT_400d046c) <= DAT_400d0470) goto LAB_400d720c;
      memw();
      memw();
      *puVar2 = *puVar2 & DAT_400d0480 | DAT_400d00e8;
      (*DAT_400d0488)(iVar1,0x100,0);
    }
    if (-1 < param_2) {
      puVar2 = *(uint **)(PTR_DAT_400d0468 + param_2 * 4);
      if ((uint)((int)puVar2 + DAT_400d046c) <= DAT_400d0470) goto LAB_400d720c;
      memw();
      memw();
      *puVar2 = *puVar2 & DAT_400d0480 | DAT_400d00e8;
      (*DAT_400d048c)(0x30,*(uint *)(PTR_DAT_400d0484 + (uint)*(byte *)(param_1 + 1) * 0x18 + 4) >>
                           0x14,0);
    }
    iVar1 = (int)param_5;
    if (-1 < iVar1) {
      puVar2 = *(uint **)(PTR_DAT_400d0468 + iVar1 * 4);
      if ((uint)((int)puVar2 + DAT_400d046c) <= DAT_400d0470) goto LAB_400d720c;
      memw();
      memw();
      *puVar2 = *puVar2 & DAT_400d0480 | DAT_400d00e8;
      (*DAT_400d0488)(iVar1,0x100,0);
    }
    if (-1 < param_4) {
      puVar2 = *(uint **)(PTR_DAT_400d0468 + param_4 * 4);
      if ((uint)((int)puVar2 + DAT_400d046c) <= DAT_400d0470) {
LAB_400d720c:
                    /* WARNING: Subroutine does not return */
        FUN_400986d4(PTR_s_gpio_ll_h_3f403382_0x7b_400d047c,0x27d,
                     PTR_s_gpio_ll_iomux_func_sel_400d0478,
                     PTR_s___Cannot_use_REG_SET_FIELD_for_D_400d0474);
      }
      memw();
      memw();
      *puVar2 = *puVar2 & DAT_400d0480 | DAT_400d00e8;
      (*DAT_400d048c)(0x30,*(uint *)(PTR_DAT_400d0484 + (uint)*(byte *)(param_1 + 1) * 0x18 + 0xc)
                           >> 0x14,0);
    }
    FUN_40093c38(*param_1,0,0);
  }
  return;
}

```

## `FUN_400d7668` @ `400d7668` size~327

```c

undefined *
FUN_400d7668(uint param_1,uint param_2,uint param_3,byte param_4,char param_5,undefined2 param_6,
            undefined2 param_7,char param_8,undefined1 param_9)

{
  undefined *puVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  undefined *puVar6;
  int *in_t0;
  undefined4 uStack_3c;
  uint uStack_38;
  uint uStack_34;
  uint uStack_30;
  undefined4 uStack_2c;
  undefined1 uStack_28;
  undefined4 uStack_24;
  
  param_1 = param_1 & 0xff;
  if (param_1 < 3) {
    puVar1 = PTR_DAT_400d04a8 + param_1 * 0xc;
    iVar2 = FUN_400dc0dc(param_1);
    if (iVar2 != 0) {
      FUN_400d73d4(puVar1);
    }
    piVar3 = (int *)(PTR_DAT_400d04a8 + param_1 * 0xc);
    if (*piVar3 == 0) goto LAB_400d7729;
    do {
      piVar3 = in_t0;
      puVar4 = (undefined4 *)(PTR_DAT_400d04a8 + param_1 * 0xc);
      do {
        iVar2 = FUN_40094190(*puVar4,0xffffffff);
      } while (iVar2 != 1);
      uStack_38 = param_3 >> 2 & 3;
      uStack_34 = param_3 & 3;
      uStack_30 = param_3 >> 4 & 3;
      uStack_2c = 0;
      uStack_28 = param_9;
      uStack_24 = 0;
      uStack_3c = FUN_400d7338(param_2);
      iVar2 = FUN_400dbe78(param_1,param_6,param_7,0x14,PTR_DAT_400d04a8 + param_1 * 0xc + 8,0);
      if (iVar2 == 0) {
        iVar2 = FUN_400db570(param_1,&uStack_3c);
        if (iVar2 == 0) {
          iVar2 = FUN_400db2b0(param_1,(int)param_5,(int)(char)param_4,0xffffffff);
          param_2 = (uint)param_4;
          if (iVar2 == 0) {
            if ((param_8 == '\0') || (iVar2 = FUN_400dae78(param_1,0x24), iVar2 == 0)) {
              FUN_40093c38(*(undefined4 *)(PTR_DAT_400d04a8 + param_1 * 0xc),0,0);
              FUN_400d7658(puVar1);
              return puVar1;
            }
            uVar5 = 0xdc;
            puVar6 = PTR_s_uart_set_line_inverse_uart_nr__U_400d04bc;
          }
          else {
            uVar5 = 0xd7;
            puVar6 = PTR_s_uart_set_pin_uart_nr__txPin__rxP_400d04b8;
          }
        }
        else {
          uVar5 = 0xd6;
          puVar6 = PTR_s_uart_param_config_uart_nr___uart_400d04b4;
        }
      }
      else {
        uVar5 = 0xd5;
        puVar6 = PTR_s_uart_driver_install_uart_nr__rx__400d04ac;
      }
      FUN_4009317c(iVar2,PTR_s_C__Users_emens_AppData_Local_Ard_400d04a4,uVar5,
                   PTR_s_uartBegin_400d04b0,puVar6);
      param_3 = 0;
      in_t0 = piVar3;
LAB_400d7729:
      iVar2 = FUN_40093e48(1);
      *piVar3 = iVar2;
    } while (iVar2 != 0);
// truncated — full in decomp_largest/
```

## `FUN_400d862c` @ `400d862c` size~323

```c

undefined4 FUN_400d862c(uint *param_1)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  
  uVar6 = *param_1;
  uVar5 = param_1[1];
  if ((uVar6 == 0 && uVar5 == 0) || ((uVar6 & DAT_400d05ac) != 0 || (uVar5 & 0xffffff00) != 0)) {
    uVar1 = FUN_40098600();
    puVar8 = PTR_s_E___u___s__GPIO_PIN_mask_error_400d05b0;
  }
  else {
    iVar4 = 0;
    if (((param_1[2] & 2) == 0) ||
       (iVar4 = 0, (uVar6 & DAT_400d05ac) == 0 && (uVar5 & 0xfffffffc) == 0)) {
      do {
        uVar2 = (*DAT_400d0394)(uVar6,uVar5,iVar4);
        if ((uVar2 & 1) != 0) {
          puVar7 = *(uint **)(PTR_DAT_400d0468 + iVar4 * 4);
          if (puVar7 == (uint *)0x0) {
            uVar1 = 0x14b;
            puVar8 = PTR_s_gpio_c_3f4042a6_0x17_400d05c0;
            puVar9 = PTR_s_gpio_config_400d05bc;
            puVar10 = PTR_s_io_reg_____intptr_t_NULL_400d05b8;
LAB_400d86b7:
                    /* WARNING: Subroutine does not return */
            FUN_400986d4(puVar8,uVar1,puVar9,puVar10);
          }
          iVar3 = FUN_400d7ca4(iVar4);
          if (iVar3 != 0) {
            FUN_400d9dc4(iVar4);
          }
          if ((param_1[2] & 1) == 0) {
            FUN_400d7cc4(iVar4);
          }
          else {
            FUN_400d7eb4();
          }
          if ((param_1[2] & 4) == 0) {
            FUN_400d7e50(iVar4);
          }
          else {
            FUN_400d7dec();
          }
          if ((param_1[2] & 2) == 0) {
            FUN_400d7d28(iVar4);
          }
          else {
            FUN_400d7f80();
          }
          if (param_1[3] == 0) {
            FUN_400d80c8(iVar4);
          }
          else {
            FUN_400d8028();
          }
          if (param_1[4] == 0) {
            FUN_400d81f0(iVar4);
          }
          else {
            FUN_400d8150();
          }
          FUN_400d8278(iVar4,param_1[5]);
          if (param_1[5] == 0) {
            FUN_400d8380(iVar4);
          }
          else {
            FUN_400d8310();
          }
          if ((uint)((int)puVar7 + DAT_400d046c) <= DAT_400d0470) {
// truncated — full in decomp_largest/
```

## `FUN_400d4574` @ `400d4574` size~294

```c

undefined4 FUN_400d4574(char *param_1,char *param_2,undefined1 param_3,int param_4,int param_5)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined8 uVar4;
  undefined *puStack_15c;
  undefined4 uStack_158;
  undefined *puStack_154;
  undefined4 uStack_150;
  undefined *puStack_14c;
  undefined4 uStack_148;
  undefined *puStack_144;
  undefined4 uStack_140;
  undefined1 auStack_13c [32];
  undefined1 auStack_11c [64];
  undefined4 uStack_dc;
  undefined1 uStack_d8;
  undefined1 auStack_d7 [6];
  undefined1 uStack_d1;
  undefined4 uStack_cc;
  undefined1 uStack_c8;
  undefined4 uStack_c4;
  undefined1 uStack_c0;
  undefined1 auStack_b0 [140];
  int iStack_24;
  
  memw();
  iStack_24 = *DAT_400d0130;
  memw();
  FUN_40090d70(auStack_13c,0,0x8c);
  uStack_dc = *DAT_400d02ac;
  uStack_cc = *DAT_400d02b0;
  uStack_c8 = 0x81;
  uStack_c0 = 1;
  uVar2 = *(undefined4 *)PTR_DAT_400d02a8;
  uStack_d1 = param_3;
  FUN_40090d70(auStack_d7,0,6);
  if ((param_1 != (char *)0x0) && (*param_1 != '\0')) {
    FUN_400d4500(auStack_13c,param_1,0x20);
    if ((param_2 != (char *)0x0) && (*param_2 != '\0')) {
      uStack_c4 = uVar2;
      FUN_400d4500(auStack_11c,param_2,0x40);
    }
    if (param_4 != 0) {
      uStack_d8 = 1;
      FUN_40090c10(auStack_d7,param_4,6);
    }
  }
  uVar4 = FUN_40126d3c(0,auStack_b0);
  puVar3 = (undefined1 *)((ulonglong)uVar4 >> 0x20);
  if ((int)uVar4 == 0) goto LAB_400d4627;
LAB_400d460c:
  do {
    uVar4 = CONCAT44(puVar3,4);
LAB_400d460e:
    memw();
    memw();
    if (iStack_24 == *DAT_400d0130) {
      return (int)uVar4;
    }
    FUN_40082e5c((int)uVar4,(int)((ulonglong)uVar4 >> 0x20));
LAB_400d4627:
    iVar1 = FUN_40090b7c(auStack_b0,auStack_13c,0x8c);
    if (iVar1 == 0) break;
    iVar1 = FUN_40126940();
    puVar3 = auStack_13c;
    if (iVar1 == 0) goto LAB_400d4651;
  } while( true );
  uVar4 = FUN_400d4558();
  if ((int)uVar4 != 3) {
LAB_400d4651:
    uVar4 = FUN_40126cd0(0,auStack_13c);
    puVar3 = (undefined1 *)((ulonglong)uVar4 >> 0x20);
    if ((int)uVar4 != 0) goto LAB_400d460c;
    if (*DAT_400d02b4 == '\0') {
      uStack_158 = *(undefined4 *)(DAT_400d02b8 + 4);
      puStack_144 = PTR_PTR_400d026c;
// truncated — full in decomp_largest/
```

## `FUN_400d380c` @ `400d380c` size~122

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

## `FUN_400d37d8` @ `400d37d8` size~50

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

## `FUN_400d36e4` @ `400d36e4` size~56

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

## `FUN_400d5014` @ `400d5014` size~71

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

## `display_display` @ `400d56b4` size~309

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
    digitalWrite(*(undefined1 *)(param_1 + 0x36),1);
    if (*(int *)(param_1 + 0x24) != 0) {
      FUN_400d3778();
    }
  }
  else {
    FUN_400d4a4c(*(int *)(param_1 + 0x28),*(undefined4 *)(param_1 + 0x3c));
  }
  return;
// truncated — full in decomp_largest/
```

## `radioTask` @ `400d236c` size~908

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
    nrf_stopListening(uVar2,0);
    nrf_startListening_or_openPipe(uVar2);
    nrf_setRetries(uVar2,0);
    nrf_setPALevel(uVar2,3,1);
    nrf_setDataRate(uVar2,1);
    nrf_setCRCLength(uVar2,0);
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
    Serial_print(uVar6,puVar3);
    Serial_println_empty(uVar6);
    Serial_print(uVar6,PTR_DAT_400d0058);
    Serial_print(uVar6,PTR_DAT_400d005c);
    Serial_print(uVar6,PTR_DAT_400d0060);
    Serial_println_empty(uVar6);
    Serial_print(uVar6,PTR_str_VSPI_SUCCESS_400d0064);
    nrf_stopListening(uVar4,0);
    nrf_startListening_or_openPipe(uVar4);
    nrf_setRetries(uVar4,0);
// truncated — full in decomp_largest/
```

## `FUN_400d2714` @ `400d2714` size~304

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
  pinMode(0x1b,3);
  FUN_400d2d68();
  pinMode(0,5);
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

## `FUN_400d2bfc` @ `400d2bfc` size~344

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
  iVar7 = digitalRead(0);
  pcVar5 = DAT_400d017c;
  piVar4 = DAT_400d0178;
  puVar2 = PTR_DAT_400d0080;
  pcVar1 = DAT_400d007c;
  if (iVar7 == 0) {
    if (*DAT_400d0178 == 0) {
      iVar7 = millis();
      *piVar4 = iVar7;
    }
    else {
      memw();
      if (((*DAT_400d007c == '\0') && (*DAT_400d017c == '\0')) &&
         (iVar7 = millis(), 499 < (uint)(iVar7 - *piVar4))) {
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
    iVar7 = millis();
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
// truncated — full in decomp_largest/
```

## `ESP32_IMAGE_ENTRY` @ `40082f0c` size~559

```c

void ESP32_IMAGE_ENTRY(void)

{
  byte bVar1;
  byte bVar2;
  undefined *puVar3;
  undefined *puVar4;
  uint *puVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  uint uVar9;
  byte *pbVar10;
  undefined1 in_PRID;
  undefined8 uVar11;
  byte bStack_39;
  undefined1 auStack_38 [10];
  byte bStack_2e;
  
  FUN_400967f4(PTR_LAB_4008062c);
  iVar6 = (*DAT_40080690)(0);
  (*DAT_40080690)(1);
  FUN_40090d70(DAT_40080660,0,DAT_4008065c - DAT_40080660);
  if (iVar6 != 5) {
    FUN_40090d70(DAT_40080668,0,DAT_40080664 - DAT_40080668);
  }
  iVar7 = (*(code *)PTR_FUN_40080694)();
  if (iVar7 != 0) {
    FUN_40082e3c();
  }
  FUN_40090078();
  (*(code *)PTR_FUN_40080698)();
  FUN_40090080();
  (*(code *)PTR_FUN_40080648)();
  pbVar10 = DAT_40080634;
  memw();
  *DAT_40080634 = 1;
  memw();
  (*(code *)PTR_FUN_4008069c)(auStack_38);
  puVar3 = PTR_DAT_40080518;
  if (bStack_2e < 2) {
    pbVar10 = PTR_DAT_40080518;
    if (*(int *)PTR_DAT_40080518 != 0) {
      uVar8 = FUN_40098600();
      puVar4 = PTR_s_cpu_start_4008066c;
      (*DAT_40080524)(PTR_s_E___u___s__Running_on_single_cor_40080670,uVar8,PTR_s_cpu_start_4008066c
                     );
      pbVar10 = *(byte **)puVar3;
      if (pbVar10 != (byte *)0x0) {
        uVar8 = FUN_40098600();
        (*DAT_40080524)(PTR_s_E___u___s__Check_that_CONFIG_FRE_40080674,uVar8,puVar4);
      }
    }
    FUN_40098648();
  }
  FUN_4008cb4c();
  (*DAT_400804b8)(1);
  FUN_4008cbb0();
  FUN_4008cb4c();
  (*DAT_40080598)(1);
  FUN_4008cbb0();
  FUN_400840fc(1);
  puVar5 = DAT_40080678;
  uVar9 = FUN_40084444(DAT_40080678);
  if ((uVar9 & 1) == 0) {
    uVar9 = FUN_40084444(puVar5);
    memw();
    *puVar5 = uVar9 | 1;
    puVar5 = DAT_4008067c;
    memw();
    uVar9 = FUN_40084444(DAT_4008067c);
    memw();
    *puVar5 = uVar9 & 0xfffffffe;
    puVar5 = DAT_40080680;
    memw();
    uVar9 = FUN_40084444(DAT_40080680);
    memw();
    *puVar5 = uVar9 | 1;
    memw();
// truncated — full in decomp_largest/
```

## `FUN_400812c4` @ `400812c4` size~611

```c

void FUN_400812c4(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint *puVar8;
  uint *puVar9;
  uint *puVar10;
  int iVar11;
  int iVar12;
  uint uVar13;
  uint uVar14;
  undefined4 uVar15;
  byte *pbVar16;
  uint uVar17;
  undefined4 uStack_28;
  undefined4 uStack_24;
  
  iVar4 = *(int *)(DAT_4008040c + param_1 * 4);
  iVar7 = *(int *)(iVar4 + 0x38);
  uStack_28 = 0;
  iVar5 = *(int *)(iVar4 + 0x10);
  if ((iVar7 == 0) || (iVar5 != 0)) {
    if ((iVar5 - 3U & 0xfffffffd) == 0) {
      if (param_2 != 0) {
        uStack_28 = 1;
        memw();
        FUN_40093e78(*(undefined4 *)(iVar4 + 0x4c),&uStack_28,param_2,2);
        return;
      }
      uVar15 = 0x525;
      goto LAB_40081448;
    }
    if (iVar5 == 4) {
      return;
    }
LAB_40081312:
    if (*(int *)(iVar4 + 0x38) != 0) {
LAB_4008135c:
      piVar3 = (int *)(PTR_DAT_40080410 + param_1 * 0x1c);
      do {
        puVar10 = *(uint **)(iVar4 + 0x38);
        if (puVar10 == (uint *)0x0) goto LAB_4008140a;
        uVar13 = *puVar10;
        uVar14 = puVar10[2];
        uVar17 = puVar10[3] - uVar14;
        iVar5 = *piVar3;
        if ((uVar13 & DAT_40080420) == DAT_40080424) {
          puVar8 = puVar10 + 1;
          uVar6 = 1;
          if (puVar10[3] != 1) {
            uVar17 = (uVar17 < 0x20) * uVar17 + (uint)(uVar17 >= 0x20) * 0x20;
            puVar8 = (uint *)(puVar10[1] + uVar14);
            uVar6 = uVar17 & 0xff;
            puVar10[2] = uVar14 + uVar17;
          }
          puVar9 = DAT_40080404;
          if (iVar5 != DAT_40080428) {
            puVar9 = DAT_40080408;
          }
          iVar7 = 0;
          while (uVar15 = DAT_4008042c, iVar7 < (int)uVar6) {
            pbVar16 = (byte *)((int)puVar8 + iVar7);
            iVar7 = iVar7 + 1;
            memw();
            *puVar9 = (uint)*pbVar16;
            memw();
          }
          iVar7 = iVar5 + *(int *)(iVar4 + 0xc) * 4;
          memw();
          *(uint *)(iVar7 + 0x58) = uVar13 & 0xffffff00 | uVar6;
          memw();
          *(undefined4 *)(iVar7 + 0x5c) = uVar15;
          memw();
// truncated — full in decomp_largest/
```

## `FUN_40080000` @ `40080000` size~15

```c

void FUN_40080000(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  undefined4 unaff_retaddr;
  
  *(undefined4 *)(param_4 + -0x10) = unaff_retaddr;
  *(BADSPACEBASE **)(param_4 + -0xc) = register0x00000004;
  *(undefined4 *)(param_4 + -8) = param_1;
  *(undefined4 *)(param_4 + -4) = param_2;
  rfwo();
  return;
}

```

Total functions CSV: 4247
