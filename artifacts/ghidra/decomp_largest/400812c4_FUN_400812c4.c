// 400812c4 FUN_400812c4 size~611

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
          *(undefined4 *)(iVar5 + 0x24) = 0xffffffff;
          memw();
          *(undefined4 *)(iVar5 + 0x28) = 0x5a8;
          *(undefined4 *)(iVar4 + 0xc) = 0;
          if ((puVar10[3] == 1) || (puVar10[2] == puVar10[3])) {
            uVar13 = puVar10[4];
            *(uint *)(iVar4 + 0x38) = uVar13;
            if (uVar13 != 0) {
              *(undefined4 *)(uVar13 + 8) = 0;
            }
          }
          uVar15 = 1;
LAB_40081407:
          *(undefined4 *)(iVar4 + 0x10) = uVar15;
          goto LAB_4008140a;
        }
        iVar7 = *(int *)(iVar4 + 0xc);
        if ((uVar13 & DAT_40080420) == DAT_40080430) {
          uVar14 = (uVar17 < 0x20) * uVar17 + (uint)(uVar17 >= 0x20) * 0x20;
          *(uint *)(iVar4 + 0x14) = uVar14;
          uVar15 = DAT_4008042c;
          memw();
          *(uint *)(iVar5 + (iVar7 + 0x14) * 4 + 8) = uVar13 & 0xffffff00 | uVar14 & 0xff;
          memw();
          *(undefined4 *)(iVar5 + (iVar7 + 0x15) * 4 + 8) = uVar15;
          memw();
          *(undefined4 *)(iVar5 + 0x24) = 0xffffffff;
          memw();
          *(undefined4 *)(iVar5 + 0x28) = 0x1a8;
          uVar15 = 0;
          memw();
          goto LAB_40081407;
        }
        uVar14 = puVar10[4];
        memw();
        *(uint *)(iVar5 + (iVar7 + 0x14) * 4 + 8) = uVar13 & 0xffffff00 | (uint)(byte)*puVar10;
        *(int *)(iVar4 + 0xc) = iVar7 + 1;
        *(uint *)(iVar4 + 0x38) = uVar14;
      } while ((iVar7 + 1 < 0xf) && (uVar14 != 0));
      *(undefined4 *)(iVar4 + 0xc) = 0;
      memw();
LAB_4008140a:
      piVar3 = (int *)(PTR_DAT_40080410 + param_1 * 0x1c);
      memw();
      FUN_40096970(piVar3);
      iVar4 = *piVar3;
      memw();
      memw();
      *(uint *)(iVar4 + 4) = *(uint *)(iVar4 + 4) | 0x20;
      memw();
      return;
    }
    memw();
  }
  else {
    iVar5 = *(int *)(PTR_DAT_40080410 + param_1 * 0x1c);
    iVar11 = *(int *)(iVar7 + 4);
    iVar12 = *(int *)(iVar7 + 8);
    bVar1 = *(byte *)(iVar4 + 0x14);
    uVar13 = 0;
    while (bVar1 != uVar13) {
      memw();
      uStack_24 = *(undefined4 *)(iVar5 + 0x1c);
      memw();
      iVar2 = uVar13 + iVar12;
      uVar13 = uVar13 + 1;
      memw();
      *(char *)(iVar11 + iVar2) = (char)uStack_24;
      memw();
      memw();
    }
    iVar5 = *(int *)(iVar7 + 8) + *(int *)(iVar4 + 0x14);
    *(int *)(iVar7 + 8) = iVar5;
    if (iVar5 != *(int *)(iVar7 + 0xc)) {
      *(undefined4 *)(iVar4 + 0xc) = 0;
      goto LAB_40081312;
    }
    iVar5 = *(int *)(*(int *)(iVar4 + 0x38) + 0x10);
    *(int *)(iVar4 + 0x38) = iVar5;
    if (iVar5 != 0) {
      *(undefined4 *)(iVar5 + 8) = 0;
      goto LAB_4008135c;
    }
  }
  if (param_2 != 0) {
    *(undefined4 *)(iVar4 + 0x3c) = 0;
    uStack_28 = 1;
    memw();
    FUN_40093e78(*(undefined4 *)(iVar4 + 0x4c),&uStack_28,param_2,2);
    *(undefined4 *)(iVar4 + 0x10) = 2;
    memw();
    return;
  }
  uVar15 = 0x52e;
  memw();
LAB_40081448:
                    /* WARNING: Subroutine does not return */
  FUN_400986d4(PTR_s_i2c_c_3f404540_0x17_4008041c,uVar15,DAT_40080418,DAT_40080414);
}


