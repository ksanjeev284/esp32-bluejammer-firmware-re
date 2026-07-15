// 400d5490 FUN_400d5490 size~331

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
        *pbVar2 = -(param_5 != 0);
        pbVar2 = pbVar2 + *(short *)(param_1 + 8);
        iVar1 = iVar1 + -1;
      } while (iVar1 != 0);
    }
    uVar3 = uVar4 - uVar5 & 7;
  }
  if (uVar3 != 0) {
    bVar6 = PTR_DAT_400d031c[uVar3];
    if (param_5 == 1) {
      bVar6 = bVar6 | *pbVar2;
    }
    else if (param_5 == 0) {
      bVar6 = (bVar6 ^ 0xff) & *pbVar2;
    }
    else {
      if (param_5 != 2) {
        return;
      }
      bVar6 = bVar6 ^ *pbVar2;
    }
    *pbVar2 = bVar6;
  }
  return;
}


