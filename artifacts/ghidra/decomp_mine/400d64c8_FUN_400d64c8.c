// 400d64c8 FUN_400d64c8

int FUN_400d64c8(uint param_1)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  
  iVar1 = DAT_400d03b8;
  param_1 = param_1 & 0xff;
  iVar2 = 0x102;
  if (param_1 < 2) {
    pcVar3 = (char *)(DAT_400d03b8 + param_1 * 0xc);
    memw();
    if (*(int *)(pcVar3 + 8) != 0) {
      memw();
      iVar2 = FUN_40094190(*(undefined4 *)(pcVar3 + 8),0xffffffff);
      if (iVar2 == 1) {
        memw();
        iVar2 = -1;
        if ((*pcVar3 != '\0') && (iVar2 = FUN_400d89f4(param_1), iVar2 == 0)) {
          memw();
          *pcVar3 = '\0';
        }
        memw();
        FUN_40093c38(*(undefined4 *)(iVar1 + param_1 * 0xc + 8),0,0);
        return iVar2;
      }
    }
    iVar2 = -1;
  }
  return iVar2;
}


