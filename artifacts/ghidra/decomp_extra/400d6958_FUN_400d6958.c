// 400d6958 FUN_400d6958

void FUN_400d6958(int param_1,char param_2)

{
  byte bVar1;
  undefined4 uVar2;
  
  if (param_1 == 0) {
    return;
  }
  bVar1 = *(byte *)(param_1 + 8);
  if (param_2 < '\0') {
    param_2 = '\f';
    uVar2 = 9;
    if (bVar1 == 2) goto LAB_400d697a;
    param_2 = '\x13';
    uVar2 = 0x40;
    if (bVar1 == 3) goto LAB_400d697a;
    param_2 = '\a';
    uVar2 = 1;
    if (bVar1 < 2) goto LAB_400d697a;
  }
  else {
    uVar2 = 1;
    if ((bVar1 < 2) || (uVar2 = 9, bVar1 == 2)) goto LAB_400d697a;
  }
  uVar2 = 0x40;
  if (bVar1 != 3) {
    uVar2 = 0;
  }
LAB_400d697a:
  FUN_400d7c84(uVar2,0);
  FUN_400d6198((int)param_2,1);
  return;
}


