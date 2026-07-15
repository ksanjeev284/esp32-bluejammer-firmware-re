// 400d60a0 FUN_400d60a0

int FUN_400d60a0(uint *param_1,uint param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint *puVar4;
  
  if (param_2 != 0) {
    if (param_3 == 0) {
      return 1;
    }
    iVar1 = (*(code *)PTR_FUN_400d0374)(param_1);
    iVar2 = FUN_400d5ffc(param_1,iVar1 + param_3);
    if (iVar2 != 0) {
      puVar4 = param_1;
      if ((*(byte *)((int)param_1 + 0xf) & 0x80) == 0) {
        puVar4 = (uint *)*param_1;
      }
      iVar3 = (*(code *)PTR_FUN_400d0374)(param_1);
      if ((param_2 < puVar4) || ((uint)((int)puVar4 + iVar3) <= param_2)) {
        FUN_40090c10((int)puVar4 + iVar3,param_2,param_3 + 1);
      }
      else {
        FUN_40090d08();
      }
      (*(code *)PTR_FUN_400d0370)(param_1,iVar1 + param_3);
      return iVar2;
    }
  }
  return 0;
}


