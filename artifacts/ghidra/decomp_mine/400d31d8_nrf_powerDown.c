// 400d31d8 nrf_powerDown

void FUN_400d31d8(int param_1)

{
  nrf_ce(param_1,0);
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfd;
  nrf_writeRegister(param_1,0);
  return;
}


