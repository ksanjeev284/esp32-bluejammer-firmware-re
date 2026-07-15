// 4015e3c8 FUN_4015e3c8

bool FUN_4015e3c8(int param_1)

{
  bool bVar1;
  
  bVar1 = false;
  if (*(int *)(param_1 + 0x10) == 0) {
    bVar1 = *(int *)(param_1 + 0x14) == 1;
  }
  return bVar1;
}


