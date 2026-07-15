// 400d32a0 FUN_400d32a0

void FUN_400d32a0(int param_1)

{
  uint uVar1;
  
  if (*(char *)(param_1 + 0x1b) != '\0') {
    uVar1 = nrf_readRegister(param_1,0x1d);
    nrf_writeRegister(param_1,0x1d,uVar1 & 0xfd);
    *(undefined1 *)(param_1 + 0x1b) = 0;
  }
  return;
}


