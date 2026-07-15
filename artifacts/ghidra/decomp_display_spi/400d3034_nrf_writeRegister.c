// 400d3034 nrf_writeRegister

void nrf_writeRegister(undefined4 *param_1,byte param_2,undefined1 param_3)

{
  undefined1 uVar1;
  
  nrf_csnLow(param_1);
  uVar1 = FUN_400d379c(*param_1,param_2 | 0x20);
  *(undefined1 *)(param_1 + 3) = uVar1;
  FUN_400d379c(*param_1,param_3);
  nrf_csnHigh(param_1);
  return;
}


