// 400d68cc FUN_400d68cc

void FUN_400d68cc(int param_1,char param_2)

{
  byte bVar1;
  undefined4 uVar2;
  
  if (param_1 != 0) {
    if (param_2 < '\0') {
      param_2 = '\r';
      if ((*(char *)(param_1 + 8) != '\x02') && (param_2 = '\x17', *(char *)(param_1 + 8) != '\x03')
         ) {
        param_2 = '\b';
      }
    }
    FUN_400d6198((int)param_2,3);
    bVar1 = *(byte *)(param_1 + 8);
    uVar2 = 2;
    if (((1 < bVar1) && (uVar2 = 10, bVar1 != 2)) && (uVar2 = 0x41, bVar1 != 3)) {
      uVar2 = 0;
    }
    FUN_400d7c40((int)param_2,uVar2,0);
  }
  return;
}


