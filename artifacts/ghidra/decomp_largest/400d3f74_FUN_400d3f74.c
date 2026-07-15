// 400d3f74 FUN_400d3f74 size~489

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
         (iVar2 = FUN_400e520c(uVar4,&uStack_38), iVar2 == 0)))) && (uStack_38 == 0)) {
      iVar2 = FUN_400e4eb8(uVar4);
    }
  }
  return iVar2;
}


