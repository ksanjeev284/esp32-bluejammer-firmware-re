// 400d6534 FUN_400d6534

void FUN_400d6534(uint param_1,uint param_2,int param_3,int param_4,undefined4 param_5,byte *param_6
                 )

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  int iStack_d8;
  undefined1 auStack_cc [168];
  int iStack_24;
  
  memw();
  iStack_24 = *DAT_400d0130;
  param_1 = param_1 & 0xff;
  memw();
  uVar3 = 0x102;
  if (1 < param_1) goto LAB_400d656c;
  iStack_d8 = param_1 * 2;
  param_6 = (byte *)(DAT_400d03b8 + param_1 * 0xc);
  memw();
  if (*(int *)(param_6 + 8) != 0) goto LAB_400d6585;
  do {
    uVar3 = 0xffffffff;
LAB_400d656c:
    while( true ) {
      param_1 = uVar3;
      param_3 = iStack_24;
      memw();
      memw();
      if (iStack_24 == *DAT_400d0130) {
        return;
      }
      FUN_40082e5c();
LAB_400d6585:
      memw();
      iVar2 = FUN_40094190(*(undefined4 *)(param_6 + 8),0xffffffff);
      if (iVar2 != 1) break;
      memw();
      bVar1 = *param_6;
      param_6 = (byte *)(uint)bVar1;
      uVar3 = 0xffffffff;
      if (bVar1 != 0) {
        FUN_40090d70(auStack_cc,0,0xa8);
        param_6 = (byte *)(*(code *)PTR_FUN_400d03c0)(auStack_cc,0xa8);
        uVar3 = FUN_400d9510();
        if (uVar3 == 0) {
          uVar3 = FUN_400d95a0(param_6,(param_2 & 0x7f) << 1,1);
          if ((uVar3 == 0) &&
             (((param_4 == 0 || (uVar3 = FUN_400d9604(param_6,param_3,param_4,1), uVar3 == 0)) &&
              (uVar3 = FUN_400d9554(param_6), uVar3 == 0)))) {
            uVar3 = FUN_400d9690(param_1,param_6,param_5);
          }
        }
        if (param_6 != (byte *)0x0) {
          (*(code *)PTR_FUN_400d03c4)(param_6);
        }
      }
      param_4 = DAT_400d03b8;
      memw();
      FUN_40093c38(*(undefined4 *)(DAT_400d03b8 + (iStack_d8 + param_1) * 4 + 8),0,0);
    }
  } while( true );
}


