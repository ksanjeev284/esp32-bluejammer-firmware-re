// 400d6198 pinMode

void FUN_400d6198(uint param_1,uint param_2)

{
  uint uVar1;
  undefined8 uStack_38;
  uint uStack_30;
  uint uStack_2c;
  undefined4 uStack_28;
  uint uStack_24;
  
  param_1 = param_1 & 0xff;
  uVar1 = (*DAT_400d0394)(DAT_400d0380,DAT_400d0384,param_1);
  if ((uVar1 & 1) != 0) {
    uStack_38 = (*DAT_400d0398)(DAT_400d0388,DAT_400d038c,param_1);
    uStack_30 = 0;
    uStack_2c = 0;
    uStack_28 = 0;
    memw();
    uStack_24 = *(uint *)(DAT_400d0390 + (param_1 + 0x20) * 4 + 8) >> 7 & 7;
    if ((param_2 & 0xff) < 0x20) {
      uStack_30 = param_2 & 3;
      if ((param_2 & 0x10) != 0) {
        uStack_30 = uStack_30 | 4;
      }
      uStack_2c = (uint)((param_2 & 4) != 0);
      if ((param_2 & 8) != 0) {
        uStack_28 = 1;
      }
    }
    FUN_400d862c(&uStack_38);
  }
  return;
}


