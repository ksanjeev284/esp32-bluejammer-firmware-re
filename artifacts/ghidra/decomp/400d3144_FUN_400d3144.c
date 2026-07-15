// 400d3144 FUN_400d3144

int FUN_400d3144(int param_1)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_FUN_400d01d8)(param_1);
  if (iVar1 != 0) {
    if (*(char *)(param_1 + 5) != *(char *)(param_1 + 4)) {
      FUN_400d6198(*(char *)(param_1 + 4),3);
      FUN_400d6198(*(undefined1 *)(param_1 + 5),3);
    }
    FUN_400d2f4c(param_1,0);
    FUN_400d2f38(param_1,1);
  }
  return iVar1;
}


