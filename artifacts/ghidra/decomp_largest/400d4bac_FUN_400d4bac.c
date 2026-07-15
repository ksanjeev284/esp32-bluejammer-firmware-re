// 400d4bac FUN_400d4bac size~773

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
        }
        else {
          sVar21 = (ushort)param_8 * (short)cVar4;
          pcVar20 = *(code **)(iVar19 + 0x24);
          sVar22 = param_5;
LAB_400d4d16:
          (*pcVar20)(param_1,(int)(short)(param_2 + (short)cVar12 * (ushort)param_7),
                     (int)(short)(param_3 + sVar21),uVar9,uVar7,sVar22);
        }
        uStack_44 = uStack_44 >> 1;
        cVar17 = cVar17 + -1;
        cVar4 = cVar4 + '\x01';
      } while (cVar17 != '\0');
      cVar12 = cVar12 + '\x01';
      cVar5 = cVar5 + -1;
    } while (cVar5 != '\0');
    if (param_5 != param_6) {
      if ((uVar9 == 1) && (uVar7 == 1)) {
        (**(code **)(*param_1 + 0x28))(param_1,(int)(short)(param_2 + 5),iVar8,8,param_6);
      }
      else {
        (**(code **)(*param_1 + 0x24))
                  (param_1,(int)(short)(param_2 + (ushort)param_7 * 5),iVar8,uVar9,uVar7 << 3,
                   param_6);
      }
    }
  }
  else {
    iVar8 = *piVar14;
    puVar11 = (ushort *)(piVar14[1] + (param_4 - *(byte *)(piVar14 + 2) & 0xff) * 8);
    uStack_5c = (uint)*puVar11;
    bVar1 = *(byte *)((int)puVar11 + 3);
    cVar5 = *(char *)((int)puVar11 + 5);
    uVar2 = puVar11[1];
    uVar3 = puVar11[3];
    if ((uVar9 < 2) && (uVar7 < 2)) {
      sStack_58 = 0;
      sStack_48 = 0;
    }
    else {
      sStack_48 = (short)cVar5;
      sStack_58 = (short)(char)uVar3;
    }
    (**(code **)(*param_1 + 0x1c))(param_1);
    uVar6 = 0;
    uVar15 = 0;
    for (uVar10 = 0; uVar10 < bVar1; uVar10 = uVar10 + 1 & 0xff) {
      uVar18 = uVar6;
      for (uVar13 = 0; uVar13 < (byte)uVar2; uVar13 = uVar13 + 1 & 0xff) {
        if ((uVar18 & 7) == 0) {
          pbVar16 = (byte *)(iVar8 + uStack_5c);
          uStack_5c = uStack_5c + 1 & 0xffff;
          uVar15 = (uint)*pbVar16;
        }
        if ((char)uVar15 < '\0') {
          if ((uVar9 == 1) && (uVar7 == 1)) {
            (**(code **)(*param_1 + 0x20))
                      (param_1,(int)(short)(param_2 + cVar5 + uVar13),
                       (int)(short)(param_3 + (char)uVar3 + uVar10),param_5);
          }
          else {
            (**(code **)(*param_1 + 0x24))
                      (param_1,(int)(short)(param_2 + (sStack_48 + uVar13) * (ushort)param_7),
                       (int)(short)(param_3 + (sStack_58 + uVar10) * (ushort)param_8),uVar9,uVar7,
                       param_5);
          }
        }
        uVar15 = (uVar15 & 0x7f) << 1;
        uVar18 = uVar18 + 1 & 0xff;
      }
      uVar6 = uVar6 + (byte)uVar2 & 0xff;
    }
  }
  (**(code **)(*param_1 + 0x34))(param_1);
  return;
}


