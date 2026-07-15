// 4015ebe4 FUN_4015ebe4

undefined4 FUN_4015ebe4(int *param_1,int *param_2)

{
  undefined4 uVar1;
  int *piVar2;
  uint uVar3;
  
  if ((*(byte *)((int)param_2 + 0xf) & 0x80) == 0) {
    piVar2 = (int *)*param_2;
    uVar3 = 0;
    if (piVar2 != (int *)0x0) {
      uVar3 = param_2[2];
    }
  }
  else {
    uVar3 = (uint)param_2[3] >> 0x18 & 0x7f;
    piVar2 = param_2;
  }
  uVar1 = (**(code **)(*param_1 + 0xc))(param_1,piVar2,uVar3);
  return uVar1;
}


