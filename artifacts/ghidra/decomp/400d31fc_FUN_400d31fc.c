// 400d31fc FUN_400d31fc

void FUN_400d31fc(int param_1)

{
  if ((*(byte *)(param_1 + 0x18) & 2) == 0) {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) | 2;
    FUN_400d3034(param_1);
    FUN_400d6730(DAT_400d01dc);
  }
  return;
}


