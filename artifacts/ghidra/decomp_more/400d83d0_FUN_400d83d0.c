// 400d83d0 FUN_400d83d0

undefined4 FUN_400d83d0(uint param_1,int param_2)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  
  uVar1 = (*DAT_400d0394)(DAT_400d0380,DAT_400d055c,param_1);
  if ((uVar1 & 1) == 0) {
    uVar2 = FUN_40098600();
    memw();
    FUN_40100120(1,PTR_DAT_400d0518,PTR_s_E___u___s___s__d____s_400d051c,uVar2,PTR_DAT_400d0518,
                 PTR_s_gpio_set_level_400d0598,0xe2,PTR_s_GPIO_output_gpio_num_error_400d0564);
    uVar2 = 0x102;
  }
  else {
    iVar3 = **(int **)PTR_PTR_400d0530;
    if (param_2 == 0) {
      if (0x1f < (int)param_1) {
        memw();
        memw();
        memw();
        memw();
        memw();
        memw();
        *(uint *)(iVar3 + 0x18) =
             *(uint *)(iVar3 + 0x18) & 0xffffff00 | 1 << 0x20 - (0x20 - (param_1 & 0x1f)) & 0xffU;
        memw();
        return 0;
      }
      memw();
      *(int *)(iVar3 + 0xc) = 1 << 0x20 - (0x20 - (param_1 & 0x1f));
      memw();
    }
    else if ((int)param_1 < 0x20) {
      memw();
      *(int *)(iVar3 + 8) = 1 << 0x20 - (0x20 - (param_1 & 0x1f));
    }
    else {
      memw();
      memw();
      memw();
      memw();
      memw();
      memw();
      *(uint *)(iVar3 + 0x14) =
           *(uint *)(iVar3 + 0x14) & 0xffffff00 | 1 << 0x20 - (0x20 - (param_1 & 0x1f)) & 0xffU;
      memw();
    }
    uVar2 = 0;
    memw();
  }
  return uVar2;
}


