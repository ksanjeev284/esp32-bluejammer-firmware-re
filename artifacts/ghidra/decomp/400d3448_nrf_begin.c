// 400d3448 nrf_begin

undefined4 nrf_begin(undefined4 *param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  *param_1 = param_2;
  iVar1 = FUN_400d3144(param_1);
  uVar2 = 0;
  if (iVar1 != 0) {
    uVar2 = FUN_400d337c(param_1);
  }
  return uVar2;
}


