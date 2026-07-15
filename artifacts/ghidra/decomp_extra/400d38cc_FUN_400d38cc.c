// 400d38cc FUN_400d38cc

int FUN_400d38cc(int param_1)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = 0;
  piVar2 = DAT_400d0200;
  while ((*piVar2 != param_1 || (*piVar2 == 0))) {
    iVar1 = iVar1 + 1;
    piVar2 = piVar2 + 1;
    if (iVar1 == 3) {
      return 3;
    }
  }
  return iVar1;
}


