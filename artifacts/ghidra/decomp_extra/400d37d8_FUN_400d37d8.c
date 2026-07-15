// 400d37d8 FUN_400d37d8

void FUN_400d37d8(uint *param_1,uint param_2)

{
  uint uVar1;
  
  *param_1 = param_2;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  FUN_400d6198(param_2 & 0xff,5);
  uVar1 = FUN_400d6224((char)*param_1);
  param_1[4] = uVar1;
  uVar1 = FUN_400d6224((char)*param_1);
  param_1[5] = uVar1;
  uVar1 = FUN_400d6224((char)*param_1);
  param_1[6] = uVar1;
  param_1[8] = 0;
  return;
}


