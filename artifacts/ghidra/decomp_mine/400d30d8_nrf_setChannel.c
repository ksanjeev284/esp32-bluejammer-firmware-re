// 400d30d8 nrf_setChannel

void nrf_setChannel(undefined4 param_1,byte param_2)

{
  if (0x7c < param_2) {
    param_2 = 0x7d;
  }
  nrf_writeRegister(param_1,5,param_2);
  return;
}


