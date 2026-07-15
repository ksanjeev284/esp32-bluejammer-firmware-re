// 400d3730 FUN_400d3730

void FUN_400d3730(int param_1,int param_2,uint param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 uStack_23;
  
  do {
    iVar1 = FUN_40094190(*(undefined4 *)(param_1 + 0x1c),0xffffffff);
  } while (iVar1 != 1);
  iVar1 = (*(code *)PTR_FUN_400d01e4)(*(undefined4 *)(param_1 + 4));
  if ((*(int *)(param_1 + 0x14) != param_2) || (*(int *)(param_1 + 0x10) != iVar1)) {
    *(int *)(param_1 + 0x14) = param_2;
    uVar2 = FUN_400d7038(param_2);
    *(undefined4 *)(param_1 + 0x10) = uVar2;
  }
  uStack_23 = (undefined1)(param_3 >> 8);
  FUN_400d6efc(*(undefined4 *)(param_1 + 4),*(undefined4 *)(param_1 + 0x10),uStack_23,param_3 & 0xff
              );
  *(undefined1 *)(param_1 + 0x18) = 1;
  return;
}


