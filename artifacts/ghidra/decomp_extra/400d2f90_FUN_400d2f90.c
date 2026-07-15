// 400d2f90 FUN_400d2f90

void FUN_400d2f90(undefined4 *param_1,undefined1 param_2,undefined1 *param_3,char param_4)

{
  undefined1 uVar1;
  
  FUN_400d2f60(param_1);
  uVar1 = FUN_400d379c(*param_1,param_2);
  *(undefined1 *)(param_1 + 3) = uVar1;
  while (param_4 = param_4 + -1, param_4 != -1) {
    uVar1 = FUN_400d379c(*param_1,0xff);
    *param_3 = uVar1;
    param_3 = param_3 + 1;
  }
  FUN_400d2f7c(param_1);
  return;
}


