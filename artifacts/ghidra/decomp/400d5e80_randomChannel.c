// 400d5e80 randomChannel

uint randomChannel(uint param_1)

{
  uint uVar1;
  
  uVar1 = 0;
  if (param_1 != 0) {
    if ((int)param_1 < 0) {
      uVar1 = FUN_400d5e70(0,-param_1);
    }
    else {
      if (*PTR_DAT_400d036c == '\0') {
        uVar1 = FUN_40090e08();
      }
      else {
        uVar1 = FUN_400841ac();
      }
      uVar1 = uVar1 % param_1;
    }
  }
  return uVar1;
}


