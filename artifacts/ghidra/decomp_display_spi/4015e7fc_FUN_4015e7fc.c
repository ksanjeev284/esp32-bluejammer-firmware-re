// 4015e7fc FUN_4015e7fc

void FUN_4015e7fc(int *param_1,short param_2,short param_3,short param_4,short param_5,
                 undefined2 param_6)

{
  int iVar1;
  int iVar2;
  
  iVar2 = (int)param_3;
  (**(code **)(*param_1 + 0x1c))(param_1);
  iVar1 = (int)param_2;
  (**(code **)(*param_1 + 0x2c))(param_1,iVar1,iVar2,(int)param_4,param_6);
  (**(code **)(*param_1 + 0x2c))
            (param_1,iVar1,(int)(short)(param_5 + -1 + param_3),(int)param_4,param_6);
  (**(code **)(*param_1 + 0x28))(param_1,iVar1,iVar2,(int)param_5,param_6);
  (**(code **)(*param_1 + 0x28))
            (param_1,(int)(short)(param_4 + -1 + param_2),iVar2,(int)param_5,param_6);
  (**(code **)(*param_1 + 0x34))(param_1);
  return;
}


