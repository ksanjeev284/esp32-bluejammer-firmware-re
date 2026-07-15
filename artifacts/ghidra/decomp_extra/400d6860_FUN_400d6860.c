// 400d6860 FUN_400d6860

void FUN_400d6860(int param_1,char param_2)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  
  if (param_1 != 0) {
    if (param_2 < '\0') {
      param_2 = '\f';
      if ((*(char *)(param_1 + 8) != '\x02') && (param_2 = '\x13', *(char *)(param_1 + 8) != '\x03')
         ) {
        param_2 = '\a';
      }
    }
    do {
      iVar2 = FUN_40094190(*(undefined4 *)(param_1 + 4),0xffffffff);
    } while (iVar2 != 1);
    FUN_400d6198((int)param_2,1);
    bVar1 = *(byte *)(param_1 + 8);
    uVar3 = 1;
    if (((1 < bVar1) && (uVar3 = 9, bVar1 != 2)) && (uVar3 = 0x40, bVar1 != 3)) {
      uVar3 = 0;
    }
    FUN_400d7c70((int)param_2,uVar3,0);
    FUN_40093c38(*(undefined4 *)(param_1 + 4),0,0);
  }
  return;
}


