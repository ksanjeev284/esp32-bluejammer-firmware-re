// 400d3b94 FUN_400d3b94 size~334

void FUN_400d3b94(void)

{
  int *piVar1;
  undefined *puVar2;
  int iVar3;
  byte *pbVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined1 auStack_2c [8];
  undefined4 *puStack_24;
  
  pbVar4 = DAT_400d021c;
  puVar5 = DAT_400d0130;
  memw();
  puStack_24 = (undefined4 *)*DAT_400d0130;
  memw();
  if (*DAT_400d021c != 0) goto LAB_400d3be3;
  *DAT_400d021c = 1;
  iVar3 = FUN_400fe3a0(auStack_2c);
  if (iVar3 == 0) {
    FUN_400fe31c(auStack_2c);
  }
  iVar3 = FUN_400e4aa4();
  *pbVar4 = iVar3 == 0;
  piVar1 = DAT_400d0220;
  if (iVar3 != 0) goto LAB_400d3be3;
  puVar6 = (undefined4 *)0x0;
  if (*DAT_400d0220 != 0) goto LAB_400d3c01;
  iVar3 = FUN_40093544();
  *piVar1 = iVar3;
  puVar7 = puVar6;
  if (iVar3 != 0) goto LAB_400d3bfb;
LAB_400d3be0:
  *pbVar4 = (byte)puVar7;
LAB_400d3be3:
  puVar6 = puStack_24;
  memw();
  memw();
  puVar5 = (undefined4 *)*puVar5;
  pbVar4 = (byte *)(uint)*pbVar4;
  if (puStack_24 == puVar5) {
    return;
  }
  iVar3 = FUN_40082e5c();
LAB_400d3bfb:
  FUN_400936d0(iVar3,DAT_400d00e8);
LAB_400d3c01:
  piVar1 = DAT_400d0204;
  if (*DAT_400d0204 == 0) goto LAB_400d3cb2;
  goto LAB_400d3c09;
LAB_400d3cb2:
  iVar3 = FUN_40093b10(0x20,4);
  *piVar1 = iVar3;
  puVar7 = puVar6;
  if (iVar3 != 0) {
LAB_400d3c09:
    iVar3 = (*(code *)PTR_FUN_400d0238)();
    piVar1 = DAT_400d0224;
    puVar7 = (undefined4 *)(uint)(iVar3 != 0 && iVar3 != 0x103);
    if (((puVar7 == (undefined4 *)0x0) &&
        (((*DAT_400d0224 != 0 ||
          (FUN_400d66e4(PTR_FUN_400d0234,PTR_s_arduino_events_400d0230,DAT_400d022c,0,0x13,
                        DAT_400d0224,1), puVar7 = puVar6, *piVar1 != 0)) &&
         (puVar2 = PTR_LAB_400d0228,
         iVar3 = (*(code *)PTR_FUN_400d023c)
                           (*(undefined4 *)PTR_PTR_400d0208,0xffffffff,PTR_LAB_400d0228,0),
         puVar7 = puVar6, iVar3 == 0)))) &&
       (((iVar3 = (*(code *)PTR_FUN_400d023c)(*(undefined4 *)PTR_PTR_400d020c,0xffffffff,puVar2,0,0)
         , iVar3 == 0 &&
         (iVar3 = (*(code *)PTR_FUN_400d023c)(*(undefined4 *)PTR_PTR_400d0214,0xffffffff,puVar2,0,0)
         , iVar3 == 0)) &&
        (iVar3 = (*(code *)PTR_FUN_400d023c)(*(undefined4 *)PTR_PTR_400d0210,0xffffffff,puVar2,0,0),
        iVar3 == 0)))) {
      iVar3 = (*(code *)PTR_FUN_400d023c)(*(undefined4 *)PTR_PTR_400d0218,0xffffffff,puVar2,0,0);
      puVar7 = (undefined4 *)(uint)(iVar3 == 0);
    }
  }
  goto LAB_400d3be0;
}


