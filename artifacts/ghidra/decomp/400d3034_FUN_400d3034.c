// 400d3034 FUN_400d3034

void FUN_400d3034(undefined4 *param_1,byte param_2,undefined1 param_3)

{
  undefined1 uVar1;
  
  FUN_400d2f60(param_1);
  uVar1 = FUN_400d379c(*param_1,param_2 | 0x20);
  *(undefined1 *)(param_1 + 3) = uVar1;
  FUN_400d379c(*param_1,param_3);
  FUN_400d2f7c(param_1);
  return;
}


