// 400d3120 nrf_isChipConnected

bool nrf_isChipConnected(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_400d2fcc(param_1,3);
  return *(byte *)(param_1 + 0x1c) - 2 == iVar1;
}


