// 400d3180 FUN_400d3180

void FUN_400d3180(int param_1)

{
  byte bVar1;
  
  FUN_400d2f4c(param_1,0);
  FUN_400d6730(*(undefined4 *)(param_1 + 0x20));
  if (*(char *)(param_1 + 0x1b) != '\0') {
    FUN_400d3078(param_1);
  }
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfe;
  FUN_400d3034(param_1,0);
  FUN_400d2ff8(param_1,10,param_1 + 0x13,*(undefined1 *)(param_1 + 0x1c));
  bVar1 = FUN_400d2fcc(param_1,2);
  FUN_400d3034(param_1,2,bVar1 | 1);
  return;
}


