// 400d6d08 FUN_400d6d08 size~370

int * FUN_400d6d08(uint param_1,undefined4 param_2,undefined1 param_3,undefined1 param_4)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  
  param_1 = param_1 & 0xff;
  if (param_1 < 4) {
    piVar1 = (int *)(PTR_DAT_400d0418 + param_1 * 0xc);
    if (piVar1[1] == 0) {
      iVar2 = FUN_40093e48(1);
      piVar1[1] = iVar2;
      if (iVar2 == 0) goto LAB_400d6d19;
    }
    puVar5 = DAT_400d041c;
    if (param_1 == 2) {
      uVar3 = FUN_40084444(DAT_400d041c);
      memw();
      *puVar5 = uVar3 | 0x40;
      puVar5 = DAT_400d0420;
      uVar4 = FUN_40084444(DAT_400d0420);
      uVar3 = 0xffffffbf;
    }
    else if (param_1 == 3) {
      uVar3 = FUN_40084444(DAT_400d041c);
      memw();
      *puVar5 = uVar3 | DAT_400d0424;
      puVar5 = DAT_400d0420;
      uVar4 = FUN_40084444(DAT_400d0420);
      uVar3 = DAT_400d0428;
    }
    else {
      uVar3 = FUN_40084444(DAT_400d041c);
      memw();
      *puVar5 = uVar3 | 2;
      puVar5 = DAT_400d0420;
      uVar4 = FUN_40084444(DAT_400d0420);
      uVar3 = 0xfffffffd;
    }
    memw();
    *puVar5 = uVar4 & uVar3;
    do {
      iVar2 = FUN_40094190(*(undefined4 *)(PTR_DAT_400d0418 + param_1 * 0xc + 4),0xffffffff);
    } while (iVar2 != 1);
    iVar2 = *piVar1;
    memw();
    memw();
    *(uint *)(iVar2 + 0x38) = *(uint *)(iVar2 + 0x38) & 0xffffffef;
    memw();
    *(undefined4 *)(iVar2 + 0x38) = 0;
    memw();
    *(undefined4 *)(iVar2 + 0x34) = 0;
    memw();
    *(undefined4 *)(iVar2 + 0x1c) = 0;
    memw();
    *(undefined4 *)(iVar2 + 0x20) = 0;
    memw();
    *(undefined4 *)(iVar2 + 8) = 0;
    memw();
    *(undefined4 *)(iVar2 + 0xc) = 0;
    memw();
    *(undefined4 *)(iVar2 + 0x14) = 0;
    memw();
    *(undefined4 *)(iVar2 + 0x18) = 0;
    memw();
    memw();
    *(uint *)(iVar2 + 0x1c) = *(uint *)(iVar2 + 0x1c) | DAT_400d042c;
    memw();
    memw();
    *(uint *)(iVar2 + 0x1c) = *(uint *)(iVar2 + 0x1c) | DAT_400d0430;
    memw();
    memw();
    *(uint *)(iVar2 + 0x1c) = *(uint *)(iVar2 + 0x1c) | 1;
    memw();
    *(undefined4 *)(iVar2 + 0x80) = 0;
    FUN_40093c38(*(undefined4 *)(PTR_DAT_400d0418 + param_1 * 0xc + 4),0,0);
    FUN_400d6ba8(piVar1,param_3);
    FUN_400d6c30(piVar1,param_4);
    FUN_400d6b80(piVar1,param_2);
    FUN_400d7a38(piVar1,PTR_LAB_400d0414);
  }
  else {
LAB_400d6d19:
    piVar1 = (int *)0x0;
  }
  return piVar1;
}


