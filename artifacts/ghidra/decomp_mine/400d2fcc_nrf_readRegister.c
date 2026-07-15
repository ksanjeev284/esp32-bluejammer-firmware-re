// 400d2fcc nrf_readRegister

undefined4 FUN_400d2fcc(undefined4 *param_1,undefined1 param_2)

{
  undefined1 uVar1;
  undefined4 uVar2;
  
  nrf_csnLow(param_1);
  uVar1 = FUN_400d379c(*param_1,param_2);
  *(undefined1 *)(param_1 + 3) = uVar1;
  uVar2 = FUN_400d379c(*param_1,0xff);
  nrf_csnHigh(param_1);
  return uVar2;
}


