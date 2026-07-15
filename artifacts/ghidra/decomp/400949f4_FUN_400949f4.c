// 400949f4 FUN_400949f4

undefined4
FUN_400949f4(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  
  uVar1 = DAT_400804d0;
  memw();
  iVar2 = FUN_40083eac(param_3,DAT_400804d0);
  uVar3 = 0xffffffff;
  if (iVar2 != 0) {
    memw();
    iVar4 = FUN_40083eac(0x158,uVar1);
    if (iVar4 == 0) {
      uVar3 = 0xffffffff;
      FUN_40098804(iVar2);
    }
    else {
      *(int *)(iVar4 + 0x34) = iVar2;
      *(undefined1 *)(iVar4 + 0x155) = 0;
      memw();
      memw();
      FUN_40094478(param_1,param_2,param_3,param_4,param_5,param_6,iVar4,0,param_7);
      FUN_400947c0(iVar4,param_7);
      uVar3 = 1;
    }
  }
  return uVar3;
}


