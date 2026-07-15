// 400d48fc FUN_400d48fc

undefined4 FUN_400d48fc(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x18) == 0) {
    iVar1 = FUN_400987e4(*(undefined4 *)(param_1 + 0x14));
    *(int *)(param_1 + 0x18) = iVar1;
    if (iVar1 == 0) {
      return 0;
    }
  }
  if (*(int *)(param_1 + 0x24) == 0) {
    iVar1 = FUN_400987e4(*(undefined4 *)(param_1 + 0x14));
    *(int *)(param_1 + 0x24) = iVar1;
    if (iVar1 == 0) {
      FUN_400d48d8(param_1);
      return 0;
    }
  }
  return 1;
}


