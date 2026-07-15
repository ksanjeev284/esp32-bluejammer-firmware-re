// 400d3460 nrf_setCRCLength

void FUN_400d3460(int param_1,int param_2)

{
  byte bVar1;
  byte bVar2;
  
  bVar2 = *(byte *)(param_1 + 0x18) & 0xf3;
  if (param_2 != 0) {
    if (param_2 == 1) {
      bVar1 = 8;
    }
    else {
      bVar1 = 0xc;
    }
    bVar2 = bVar2 | bVar1;
  }
  *(byte *)(param_1 + 0x18) = bVar2;
  nrf_writeRegister(param_1,0,*(undefined1 *)(param_1 + 0x18));
  return;
}


