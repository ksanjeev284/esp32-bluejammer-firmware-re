// 400d5ac4 FUN_400d5ac4

void FUN_400d5ac4(int param_1,uint param_2,undefined4 param_3,uint param_4,uint param_5,
                 undefined1 param_6,uint param_7,undefined1 param_8)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 uVar4;
  char cVar5;
  char cVar7;
  uint uVar8;
  char cVar9;
  uint uVar6;
  
  uVar6 = param_4 & 0xff;
  cVar5 = (char)param_4;
  uVar8 = param_5 & 0xff;
  cVar7 = (char)param_5;
  if (2 < *(uint *)(param_1 + 0x10)) {
    return;
  }
  if (*(int *)(param_1 + 0x48) == 0) {
    return;
  }
  do {
    iVar1 = FUN_40094190(*(undefined4 *)(param_1 + 0x48),0xffffffff);
  } while (iVar1 != 1);
  iVar1 = FUN_400d7358(*(undefined4 *)(param_1 + 0x14));
  if (iVar1 == 0) {
    iVar1 = *(int *)(param_1 + 0x10);
    if (iVar1 == 1) {
      if (uVar6 >> 7 != 0) {
        if (uVar8 >> 7 != 0) {
          cVar7 = '\n';
        }
        cVar9 = '\t';
        goto LAB_400d5b1b;
      }
    }
    else if (iVar1 == 2) {
      if (uVar6 >> 7 != 0) {
        if (uVar8 >> 7 != 0) {
          cVar7 = '\x11';
        }
        cVar9 = '\x10';
LAB_400d5b1b:
        if (uVar8 >> 7 != 0) {
          cVar5 = cVar9;
        }
      }
    }
    else if ((iVar1 == 0) && (uVar6 >> 7 != 0)) {
      if (uVar8 >> 7 != 0) {
        cVar7 = '\x01';
      }
      cVar9 = '\x03';
      goto LAB_400d5b1b;
    }
  }
  if (*(int *)(param_1 + 0x14) != 0) {
    FUN_400d59f4(param_1,0);
  }
  uVar6 = param_2;
  if (param_2 == 0) {
    uVar6 = DAT_400d0358;
  }
  uVar2 = FUN_400d7668(*(undefined1 *)(param_1 + 0x10),uVar6,param_3,(int)cVar5,(int)cVar7,
                       *(undefined2 *)(param_1 + 0x18),*(undefined2 *)(param_1 + 0x1c),param_6,
                       param_8);
  *(undefined4 *)(param_1 + 0x14) = uVar2;
  if (param_2 == 0) {
    FUN_400d7878();
    iVar1 = millis();
    while (iVar3 = millis(), (uint)(iVar3 - iVar1) < param_7) {
      iVar3 = FUN_400d78c8(*(undefined4 *)(param_1 + 0x14));
      if (iVar3 != 0) goto LAB_400d5bae;
      FUN_400d66dc();
    }
    iVar3 = 0;
LAB_400d5bae:
    FUN_400d59f4(param_1,0);
    if (iVar3 == 0) {
      *(undefined4 *)(param_1 + 0x14) = 0;
      goto LAB_400d5c05;
    }
    delay_ms(100);
    uVar2 = FUN_400d7668(*(undefined1 *)(param_1 + 0x10),iVar3,param_3,(int)cVar5,(int)cVar7,
                         *(undefined2 *)(param_1 + 0x18),*(undefined2 *)(param_1 + 0x1c),param_6,
                         param_8);
    *(undefined4 *)(param_1 + 0x14) = uVar2;
  }
  if ((*(int *)(param_1 + 0x14) != 0) &&
     (((*(int *)(param_1 + 0x28) != 0 || (*(int *)(param_1 + 0x38) != 0)) &&
      (*(int *)(param_1 + 0x44) == 0)))) {
    FUN_400d59c0(param_1,param_1);
  }
LAB_400d5c05:
  FUN_400d736c(*(undefined4 *)(param_1 + 0x14),*(undefined1 *)(param_1 + 0x41));
  if (*(char *)(param_1 + 0x42) == '\0') {
    uVar4 = 0x78;
    if (((param_2 <= DAT_400d035c) && (uVar4 = 1, *(int *)(param_1 + 0x28) != 0)) &&
       (*(char *)(param_1 + 0x40) != '\0')) {
      uVar4 = 0x78;
    }
    FUN_400d73a0(*(undefined4 *)(param_1 + 0x14),uVar4);
    *(undefined1 *)(param_1 + 0x42) = uVar4;
  }
  *(char *)(param_1 + 0x4c) = cVar5;
  *(char *)(param_1 + 0x4d) = cVar7;
  FUN_40093c38(*(undefined4 *)(param_1 + 0x48),0,0);
  return;
}


