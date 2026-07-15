// 400d4574 FUN_400d4574 size~294

undefined4 FUN_400d4574(char *param_1,char *param_2,undefined1 param_3,int param_4,int param_5)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined8 uVar4;
  undefined *puStack_15c;
  undefined4 uStack_158;
  undefined *puStack_154;
  undefined4 uStack_150;
  undefined *puStack_14c;
  undefined4 uStack_148;
  undefined *puStack_144;
  undefined4 uStack_140;
  undefined1 auStack_13c [32];
  undefined1 auStack_11c [64];
  undefined4 uStack_dc;
  undefined1 uStack_d8;
  undefined1 auStack_d7 [6];
  undefined1 uStack_d1;
  undefined4 uStack_cc;
  undefined1 uStack_c8;
  undefined4 uStack_c4;
  undefined1 uStack_c0;
  undefined1 auStack_b0 [140];
  int iStack_24;
  
  memw();
  iStack_24 = *DAT_400d0130;
  memw();
  FUN_40090d70(auStack_13c,0,0x8c);
  uStack_dc = *DAT_400d02ac;
  uStack_cc = *DAT_400d02b0;
  uStack_c8 = 0x81;
  uStack_c0 = 1;
  uVar2 = *(undefined4 *)PTR_DAT_400d02a8;
  uStack_d1 = param_3;
  FUN_40090d70(auStack_d7,0,6);
  if ((param_1 != (char *)0x0) && (*param_1 != '\0')) {
    FUN_400d4500(auStack_13c,param_1,0x20);
    if ((param_2 != (char *)0x0) && (*param_2 != '\0')) {
      uStack_c4 = uVar2;
      FUN_400d4500(auStack_11c,param_2,0x40);
    }
    if (param_4 != 0) {
      uStack_d8 = 1;
      FUN_40090c10(auStack_d7,param_4,6);
    }
  }
  uVar4 = FUN_40126d3c(0,auStack_b0);
  puVar3 = (undefined1 *)((ulonglong)uVar4 >> 0x20);
  if ((int)uVar4 == 0) goto LAB_400d4627;
LAB_400d460c:
  do {
    uVar4 = CONCAT44(puVar3,4);
LAB_400d460e:
    memw();
    memw();
    if (iStack_24 == *DAT_400d0130) {
      return (int)uVar4;
    }
    FUN_40082e5c((int)uVar4,(int)((ulonglong)uVar4 >> 0x20));
LAB_400d4627:
    iVar1 = FUN_40090b7c(auStack_b0,auStack_13c,0x8c);
    if (iVar1 == 0) break;
    iVar1 = FUN_40126940();
    puVar3 = auStack_13c;
    if (iVar1 == 0) goto LAB_400d4651;
  } while( true );
  uVar4 = FUN_400d4558();
  if ((int)uVar4 != 3) {
LAB_400d4651:
    uVar4 = FUN_40126cd0(0,auStack_13c);
    puVar3 = (undefined1 *)((ulonglong)uVar4 >> 0x20);
    if ((int)uVar4 != 0) goto LAB_400d460c;
    if (*DAT_400d02b4 == '\0') {
      uStack_158 = *(undefined4 *)(DAT_400d02b8 + 4);
      puStack_144 = PTR_PTR_400d026c;
      puStack_14c = PTR_PTR_400d026c;
      puStack_154 = PTR_PTR_400d026c;
      puStack_15c = PTR_PTR_400d026c;
      uStack_150 = uStack_158;
      uStack_148 = uStack_158;
      uStack_140 = uStack_158;
      uVar4 = FUN_400d3f74(0,&puStack_144,&puStack_14c,&puStack_154,&puStack_15c);
      puVar3 = (undefined1 *)((ulonglong)uVar4 >> 0x20);
      if ((int)uVar4 != 0) goto LAB_400d460c;
    }
    if (param_5 != 0) {
      uVar4 = FUN_401268f8();
      puVar3 = (undefined1 *)((ulonglong)uVar4 >> 0x20);
      if ((int)uVar4 != 0) goto LAB_400d460c;
    }
    uVar4 = FUN_400d4558();
  }
  goto LAB_400d460e;
}


