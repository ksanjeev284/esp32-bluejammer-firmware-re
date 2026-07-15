// 400d493c FUN_400d493c

undefined4 FUN_400d493c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  if (*(int *)(param_1 + 0x3c) == 0) {
    iVar1 = FUN_40093e48(1);
    *(int *)(param_1 + 0x3c) = iVar1;
    if (iVar1 == 0) {
      return 0;
    }
  }
  iVar1 = FUN_40094190(*(undefined4 *)(param_1 + 0x3c),0xffffffff);
  if (iVar1 != 1) {
    return 0;
  }
  if ((*(char *)(param_1 + 0x40) == '\0') &&
     ((iVar1 = FUN_400d63ac(*(undefined1 *)(param_1 + 0x10)), iVar1 != 0 ||
      (((iVar1 = FUN_400d48fc(param_1), iVar1 != 0 &&
        (iVar1 = (*(code *)PTR_FUN_400d02d8)(param_1,param_2,param_3), iVar1 != 0)) &&
       (iVar1 = FUN_400d63d0(*(undefined1 *)(param_1 + 0x10),(int)*(char *)(param_1 + 0x11),
                             (int)*(char *)(param_1 + 0x12),param_4), iVar1 == 0)))))) {
    uVar2 = 1;
  }
  else {
    FUN_400d48d8(param_1);
    uVar2 = 0;
  }
  FUN_40093c38(*(undefined4 *)(param_1 + 0x3c),0,0);
  return uVar2;
}


