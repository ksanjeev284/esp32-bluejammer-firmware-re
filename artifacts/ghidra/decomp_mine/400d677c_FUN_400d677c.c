// 400d677c FUN_400d677c

void FUN_400d677c(void)

{
  int iVar1;
  undefined4 uVar2;
  int aiStack_24 [9];
  
  iVar1 = (*(code *)PTR_FUN_400d03e4)();
  if (iVar1 == 0) {
    uVar2 = FUN_400dc33c();
    iVar1 = FUN_400dc56c(uVar2,aiStack_24);
    if ((iVar1 == 0) && (aiStack_24[0] == 1)) {
      iVar1 = (*(code *)PTR_FUN_400d03e8)();
      if (iVar1 == 0) {
        FUN_400dc560();
      }
      else {
        FUN_400dc554();
      }
    }
  }
  FUN_400d7b0c(0xf0);
  (*(code *)PTR_FUN_400d03ec)(PTR_DAT_400d03d8,1);
  iVar1 = FUN_400dd5f0();
  if ((((iVar1 + DAT_400d03dc == 0) || (iVar1 + DAT_400d03e0 == 0)) &&
      (iVar1 = FUN_400dd0e8(1,2,0), iVar1 != 0)) &&
     (iVar1 = FUN_400dd1cc(iVar1,0,*(undefined4 *)(iVar1 + 0x10)), iVar1 == 0)) {
    FUN_400dd5f0();
  }
  iVar1 = (*(code *)PTR_FUN_400d03f0)();
  if (iVar1 == 0) {
    FUN_400fefa0(3);
  }
  (*(code *)PTR_FUN_400d03f4)();
  (*(code *)PTR_FUN_400d03f8)();
  return;
}


