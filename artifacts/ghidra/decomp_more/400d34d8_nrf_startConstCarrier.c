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
  FUN_400d3180(param_1);
  bVar2 = FUN_400d2fcc(param_1,6);
  FUN_400d3034(param_1,6,bVar2 | 0x90);
  if (*(char *)(param_1 + 0x19) != '\0') {
    FUN_400d32c4(param_1,0);
    FUN_400d3034(param_1,4,0);
    local_44[0] = 0xff;
    FUN_400d2ff8(param_1,0x10,local_44,5);
    FUN_400d3078(param_1);
    FUN_400d2ff8(param_1,0xa0,local_44,0x20);
    FUN_400d3494(param_1);
  }
  FUN_400d32f4(param_1,param_2,1);
  nrf_setChannel(param_1,param_3);
  FUN_400d2f4c(param_1,1);
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


