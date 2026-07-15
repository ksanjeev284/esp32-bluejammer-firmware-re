// 400d3180 nrf_startListening_or_openPipe

void FUN_400d3180(int param_1)

{
  byte bVar1;
  
  nrf_ce(param_1,0);
  FUN_400d6730(*(undefined4 *)(param_1 + 0x20));
  if (*(char *)(param_1 + 0x1b) != '\0') {
    nrf_flushTx(param_1);
  }
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfe;
  nrf_writeRegister(param_1,0);
  nrf_writeBytes(param_1,10,param_1 + 0x13,*(undefined1 *)(param_1 + 0x1c));
  bVar1 = nrf_readRegister(param_1,2);
  nrf_writeRegister(param_1,2,bVar1 | 1);
  return;
}


