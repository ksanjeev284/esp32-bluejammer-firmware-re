// 400d30f0 nrf_setPayloadSize

void FUN_400d30f0(int param_1,byte param_2)

{
  int iVar1;
  int iVar2;
  char cVar3;
  
  cVar3 = '\x01';
  if (param_2 != 0) {
    cVar3 = (param_2 < 0x20) * param_2 + (param_2 >= 0x20) * ' ';
  }
  *(char *)(param_1 + 0xd) = cVar3;
  iVar1 = 0x11;
  do {
    iVar2 = iVar1 + 1;
    nrf_writeRegister(param_1,iVar1,*(undefined1 *)(param_1 + 0xd));
    iVar1 = iVar2;
  } while (iVar2 != 0x17);
  return;
}


