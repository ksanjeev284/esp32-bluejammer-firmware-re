// 400d862c FUN_400d862c size~323

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
            uVar1 = 0x27d;
            puVar8 = PTR_s_gpio_ll_h_3f404036_0x26_400d0540;
            puVar9 = PTR_s_gpio_ll_iomux_func_sel_400d05c8;
            puVar10 = PTR_s___Cannot_use_REG_SET_FIELD_for_D_400d05c4;
            goto LAB_400d86b7;
          }
          memw();
          memw();
          *puVar7 = *puVar7 & DAT_400d0480 | DAT_400d00e8;
        }
        iVar4 = iVar4 + 1;
        if (iVar4 == 0x28) {
          memw();
          return 0;
        }
      } while( true );
    }
    uVar1 = FUN_40098600();
    puVar8 = PTR_s_E___u___s__GPIO_can_only_be_used_400d05b4;
  }
  FUN_40100120(1,PTR_DAT_400d0518,puVar8,uVar1,PTR_DAT_400d0518);
  return 0x102;
}


