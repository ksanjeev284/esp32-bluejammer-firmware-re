// 400d71d0 FUN_400d71d0 size~360

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


