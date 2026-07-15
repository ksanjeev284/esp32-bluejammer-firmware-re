// 400d680c FUN_400d680c

void FUN_400d680c(int param_1,char param_2)

{
  byte bVar1;
  undefined4 uVar2;
  
  if (param_1 != 0) {
    if (param_2 < '\0') {
      param_2 = '\x0e';
      if ((*(char *)(param_1 + 8) != '\x02') && (param_2 = '\x12', *(char *)(param_1 + 8) != '\x03')
         ) {
        param_2 = '\x06';
      }
    }
    FUN_400d6198((int)param_2,3);
    bVar1 = *(byte *)(param_1 + 8);
    uVar2 = 0;
    if (((1 < bVar1) && (uVar2 = 8, bVar1 != 2)) && (uVar2 = 0, bVar1 == 3)) {
      uVar2 = 0x3f;
    }
    FUN_400d7c40((int)param_2,uVar2,0);
  }
  return;
}


