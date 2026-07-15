// 400d6260 FUN_400d6260

void FUN_400d6260(int *param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  if (-1 < *(char *)((int)param_1 + 6)) {
    (*DAT_400d03ac)((int)*(char *)((int)param_1 + 6),0x100,0);
    uVar3 = 0x1d;
    if (((char)param_1[1] != '\0') && (uVar3 = 0x5f, (char)param_1[1] != '\x01')) {
      uVar3 = 0;
    }
    (*DAT_400d03b0)(0x30,uVar3,0);
    FUN_400d6234((int)*(char *)((int)param_1 + 6),1);
    *(undefined1 *)((int)param_1 + 6) = 0xff;
  }
  if (-1 < *(char *)((int)param_1 + 5)) {
    (*DAT_400d03ac)((int)*(char *)((int)param_1 + 5),0x100,0);
    uVar3 = 0x1e;
    if (((char)param_1[1] != '\0') && (uVar3 = 0x60, (char)param_1[1] != '\x01')) {
      uVar3 = 0;
    }
    (*DAT_400d03b0)(0x30,uVar3,0);
    FUN_400d6234((int)*(char *)((int)param_1 + 5),1);
    *(undefined1 *)((int)param_1 + 5) = 0xff;
  }
  iVar1 = *param_1;
  memw();
  memw();
  *(uint *)(iVar1 + 0x10) = *(uint *)(iVar1 + 0x10) & DAT_400d039c;
  memw();
  memw();
  *(uint *)(iVar1 + 0x10) = *(uint *)(iVar1 + 0x10) & DAT_400d03a0;
  memw();
  memw();
  *(uint *)(iVar1 + 0x28) = *(uint *)(iVar1 + 0x28) & DAT_400d03a4;
  iVar2 = param_1[5];
  memw();
  *(undefined4 *)(iVar1 + 0x24) = DAT_400d03a8;
  if (iVar2 != 0) {
    FUN_400fe208();
    param_1[5] = 0;
  }
  if (param_1[6] != 0) {
    FUN_40095628();
    param_1[6] = 0;
  }
  if (param_1[8] != 0) {
    FUN_40093008();
    param_1[8] = 0;
  }
  if (param_1[9] != 0) {
    FUN_40094454();
    param_1[9] = 0;
  }
  if (param_1[7] != 0) {
    FUN_40094454();
    param_1[7] = 0;
  }
  param_1[10] = 0;
  return;
}


