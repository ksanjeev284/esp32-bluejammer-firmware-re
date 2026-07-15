// 4015e79c FUN_4015e79c

void FUN_4015e79c(int *param_1,short param_2,short param_3,short param_4,short param_5,
                 undefined2 param_6)

{
  int iVar1;
  int iVar2;
  
  iVar1 = (int)param_2;
  (**(code **)(*param_1 + 0x1c))(param_1);
  iVar2 = iVar1 + param_4;
  for (; iVar1 < iVar2; iVar1 = (int)(short)((short)iVar1 + 1)) {
    (**(code **)(*param_1 + 0x28))(param_1,iVar1,(int)param_3,(int)param_5,param_6);
  }
  (**(code **)(*param_1 + 0x34))(param_1);
  return;
}


