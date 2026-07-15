// 400d7038 FUN_400d7038

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


