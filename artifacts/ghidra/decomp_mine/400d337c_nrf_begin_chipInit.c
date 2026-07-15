// 400d337c nrf_begin_chipInit

bool FUN_400d337c(int param_1)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  
  delay_ms(5);
  nrf_writeRegister(param_1,4,0x5f);
  nrf_setDataRate(param_1,0);
  iVar2 = nrf_readRegister(param_1,0x1d);
  FUN_400d327c(param_1);
  iVar3 = nrf_readRegister(param_1,0x1d);
  *(bool *)(param_1 + 0x19) = iVar2 == iVar3;
  if (iVar3 != 0) {
    if (iVar2 == iVar3) {
      FUN_400d327c(param_1);
    }
    nrf_writeRegister(param_1,0x1d,0);
  }
  *(undefined1 *)(param_1 + 0x1b) = 0;
  nrf_writeRegister(param_1,0x1c,0);
  *(undefined1 *)(param_1 + 0x1d) = 0;
  nrf_writeRegister(param_1,1,0x3f);
  nrf_writeRegister(param_1,2,3);
  nrf_setPayloadSize(param_1,0x20);
  nrf_setAddressWidth(param_1,5);
  nrf_setChannel(param_1,0x4c);
  nrf_writeRegister(param_1,7,0x70);
  nrf_flushRx(param_1);
  nrf_flushTx(param_1);
  nrf_writeRegister(param_1,0,0xc);
  uVar1 = nrf_readRegister(param_1,0);
  *(undefined1 *)(param_1 + 0x18) = uVar1;
  nrf_powerUp(param_1);
  return *(char *)(param_1 + 0x18) == '\x0e';
}


