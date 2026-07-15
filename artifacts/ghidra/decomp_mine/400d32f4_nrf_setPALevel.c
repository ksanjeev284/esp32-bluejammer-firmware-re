// 400d32f4 nrf_setPALevel

void FUN_400d32f4(undefined4 param_1,byte param_2,char param_3)

{
  byte bVar1;
  
  bVar1 = nrf_readRegister(param_1,6);
  nrf_writeRegister(param_1,6,
                    bVar1 & 0xf8 |
                    param_3 + ((param_2 < 3) * param_2 + (param_2 >= 3) * '\x03') * '\x02');
  return;
}


