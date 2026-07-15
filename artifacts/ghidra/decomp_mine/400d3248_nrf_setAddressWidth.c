// 400d3248 nrf_setAddressWidth

void FUN_400d3248(int param_1,char param_2)

{
  byte bVar1;
  
  if ((byte)(param_2 - 2U) == 0) {
    nrf_writeRegister(param_1,3);
    *(undefined1 *)(param_1 + 0x1c) = 2;
  }
  else {
    bVar1 = param_2 - 2U & 3;
    nrf_writeRegister(param_1,3,bVar1);
    *(byte *)(param_1 + 0x1c) = bVar1 + 2;
  }
  return;
}


