// 400d3220 FUN_400d3220

void FUN_400d3220(undefined4 param_1)

{
  nrf_ce(param_1,0);
  nrf_writeRegister(param_1,7,0x10);
  nrf_writeCmd(param_1,0xe3,0);
  nrf_ce(param_1,1);
  return;
}


