// 400d6150 FUN_400d6150

bool FUN_400d6150(void)

{
  int iVar1;
  
  iVar1 = FUN_400ff0e4();
  if (iVar1 == 0) {
    return true;
  }
  iVar1 = FUN_400ff0e4();
  if (iVar1 == 2) {
    iVar1 = FUN_400ff094();
    if (iVar1 != 0) {
      return false;
    }
    do {
      iVar1 = FUN_400ff0e4();
    } while (iVar1 == 2);
  }
  iVar1 = FUN_400ff0e4();
  if ((iVar1 == 1) && (iVar1 = FUN_400ff078(), iVar1 == 0)) {
    FUN_40095724(1);
    iVar1 = FUN_400ff0e4();
    return iVar1 == 0;
  }
  return false;
}


