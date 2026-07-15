// 400d2a24 FUN_400d2a24

void FUN_400d2a24(void)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined *puVar6;
  int aiStack_34 [2];
  uint uStack_2c;
  uint uStack_28;
  int iStack_24;
  
  piVar2 = DAT_400d0130;
  piVar1 = DAT_400d0108;
  memw();
  iStack_24 = *DAT_400d0130;
  memw();
  if (*DAT_400d0108 != 0) {
    Serial_print(DAT_400d0028,PTR_str_State0_Idle_400d013c);
    *piVar1 = 0;
  }
  piVar1 = DAT_400d0140;
  *DAT_400d0140 = *DAT_400d0140 + 1;
  iVar4 = DAT_400d0144;
  display_clearDisplay(DAT_400d0144);
  FUN_400d4fd8(iVar4,1);
  puVar6 = PTR_DAT_400d0148;
  *(undefined4 *)(iVar4 + 0x10) = 0;
  FUN_400d5d08(iVar4,puVar6);
  iVar3 = nrf_isChipConnected(DAT_400d0024);
  puVar6 = PTR_s_OK_3f406b01_0x11_400d0134;
  if (iVar3 == 0) {
    puVar6 = PTR_s_FAIL_3f40eb3c_0x1a_400d0138;
  }
  FUN_400d5d08(iVar4,puVar6);
  puVar6 = PTR_DAT_400d0150;
  *(undefined4 *)(iVar4 + 0x10) = DAT_400d014c;
  FUN_400d5d08(iVar4,puVar6);
  iVar3 = nrf_isChipConnected(DAT_400d0054);
  puVar6 = PTR_s_OK_3f406b01_0x11_400d0134;
  if (iVar3 == 0) {
    puVar6 = PTR_s_FAIL_3f40eb3c_0x1a_400d0138;
  }
  FUN_400d5d08(iVar4,puVar6);
  (*(code *)PTR_FUN_400d016c)(iVar4,0x3c,10,8,0xc,1);
  (*(code *)PTR_FUN_400d0170)(iVar4,0x3d,0xb,6,3,1);
  (*(code *)PTR_FUN_400d0170)(iVar4,0x38,0x10,0x10,2,1);
  (*(code *)PTR_FUN_400d0170)(iVar4,0x36,0x14,4,2,1);
  (*(code *)PTR_FUN_400d0170)(iVar4,0x3e,0x14,4,2,1);
  (*(code *)PTR_FUN_400d0170)(iVar4,0x46,0x14,4,2,1);
  FUN_400d4fd8(iVar4,1);
  puVar6 = PTR_DAT_400d0158;
  *(undefined4 *)(iVar4 + 0x10) = DAT_400d0154;
  FUN_400d5d08(iVar4,puVar6);
  uVar5 = (int)((longlong)*piVar1 * (longlong)DAT_400d015c >> 0x22) - (*piVar1 >> 0x1f) &
          DAT_400d0160;
  if ((int)uVar5 < 0) {
    uVar5 = (uVar5 - 1 | 0xfffffffc) + 1;
  }
  FUN_400d6084(aiStack_34,PTR_str_Connected_400d0164);
  for (iVar3 = 0; iVar3 < (int)uVar5; iVar3 = iVar3 + 1) {
    FUN_400d6100(aiStack_34,PTR_DAT_400d0168);
  }
  if ((uStack_28 & 0x80000000) != 0) goto LAB_400d2bf0;
  uVar5 = 0;
  if (aiStack_34[0] != 0) {
    uVar5 = uStack_2c;
  }
  while( true ) {
    *(short *)(iVar4 + 0x10) = (short)(uVar5 * -6 + 0x80 >> 1);
    *(undefined2 *)(iVar4 + 0x12) = 0x26;
    (*(code *)PTR_FUN_400d0174)(iVar4,aiStack_34);
    display_display(iVar4);
    FUN_400d5eec(aiStack_34);
    memw();
    memw();
    iVar4 = *piVar2;
    if (iStack_24 == iVar4) break;
    FUN_40082e5c();
    FUN_400d5eec(aiStack_34);
    (*(code *)PTR_FUN_400d008c)(iVar4);
LAB_400d2bf0:
    uVar5 = uStack_28 >> 0x18 & 0x7f;
  }
  return;
}


