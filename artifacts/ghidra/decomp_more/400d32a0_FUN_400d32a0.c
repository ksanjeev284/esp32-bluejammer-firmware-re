// 400d32a0 FUN_400d32a0

void FUN_400d32a0(int param_1)

{
  uint uVar1;
  
  if (*(char *)(param_1 + 0x1b) != '\0') {
    uVar1 = FUN_400d2fcc(param_1,0x1d);
    FUN_400d3034(param_1,0x1d,uVar1 & 0xfd);
    *(undefined1 *)(param_1 + 0x1b) = 0;
  }
  return;
}


