// 400d3590 FUN_400d3590

void FUN_400d3590(int param_1)

{
  uint uVar1;
  
  FUN_400d31d8(param_1);
  uVar1 = FUN_400d2fcc(param_1,6);
  FUN_400d3034(param_1,6,uVar1 & 0x6f);
  FUN_400d2f4c(param_1,0);
  FUN_400d3078(param_1);
  if (*(char *)(param_1 + 0x19) != '\0') {
    FUN_400d2ff8(param_1,0x10,param_1 + 0x13,*(undefined1 *)(param_1 + 0x1c));
  }
  return;
}


