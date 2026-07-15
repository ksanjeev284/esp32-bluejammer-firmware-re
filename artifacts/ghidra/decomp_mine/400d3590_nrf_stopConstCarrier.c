// 400d3590 nrf_stopConstCarrier

void FUN_400d3590(int param_1)

{
  uint uVar1;
  
  nrf_powerDown(param_1);
  uVar1 = nrf_readRegister(param_1,6);
  nrf_writeRegister(param_1,6,uVar1 & 0x6f);
  nrf_ce(param_1,0);
  nrf_flushTx(param_1);
  if (*(char *)(param_1 + 0x19) != '\0') {
    nrf_writeBytes(param_1,0x10,param_1 + 0x13,*(undefined1 *)(param_1 + 0x1c));
  }
  return;
}


