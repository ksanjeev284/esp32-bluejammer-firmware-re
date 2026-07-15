// 400d34d8 nrf_startConstCarrier

void nrf_startConstCarrier(int param_1,undefined1 param_2,undefined1 param_3)

{
  int *piVar1;
  byte bVar2;
  undefined1 local_44 [32];
  int iStack_24;
  
  piVar1 = DAT_400d0130;
  memw();
  iStack_24 = *DAT_400d0130;
  memw();
  nrf_startListening_or_openPipe(param_1);
  bVar2 = nrf_readRegister(param_1,6);
  nrf_writeRegister(param_1,6,bVar2 | 0x90);
  if (*(char *)(param_1 + 0x19) != '\0') {
    nrf_stopListening(param_1,0);
    nrf_writeRegister(param_1,4,0);
    local_44[0] = 0xff;
    nrf_writeBytes(param_1,0x10,local_44,5);
    nrf_flushTx(param_1);
    nrf_writeBytes(param_1,0xa0,local_44,0x20);
    FUN_400d3494(param_1);
  }
  nrf_setPALevel(param_1,param_2,1);
  nrf_setChannel(param_1,param_3);
  nrf_ce(param_1,1);
  if (*(char *)(param_1 + 0x19) != '\0') {
    delay_ms(1);
    FUN_400d3220(param_1);
  }
  memw();
  memw();
  if (iStack_24 != *piVar1) {
    FUN_40082e5c();
  }
  return;
}


