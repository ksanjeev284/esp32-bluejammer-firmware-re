// 400d604c FUN_400d604c

void FUN_400d604c(int *param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = FUN_400d5ffc(param_1,param_3);
  if (iVar1 == 0) {
    FUN_400d5ed4(param_1);
  }
  else {
    piVar2 = param_1;
    if ((*(byte *)((int)param_1 + 0xf) & 0x80) == 0) {
      piVar2 = (int *)*param_1;
    }
    FUN_40090d08(piVar2,param_2,param_3 + 1);
    (*(code *)PTR_FUN_400d0370)(param_1,param_3);
  }
  return;
}


