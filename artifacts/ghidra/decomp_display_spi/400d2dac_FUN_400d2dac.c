// 400d2dac FUN_400d2dac

void FUN_400d2dac(int param_1,char param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  ushort uVar4;
  undefined *puVar5;
  int aiStack_34 [3];
  undefined4 uStack_28;
  int iStack_24;
  
  iVar2 = DAT_400d0144;
  piVar1 = DAT_400d0130;
  memw();
  iStack_24 = *DAT_400d0130;
  memw();
  display_clearDisplay(DAT_400d0144);
  iVar3 = 0;
  if (param_2 == '\0') goto LAB_400d2e12;
  iVar3 = FUN_400910b8(param_1,PTR_str_bitmapboot_400d0198);
  if (iVar3 == 0) {
    (*(code *)PTR_FUN_400d01c4)(iVar2,0,0,PTR_bitmap_boot_or_extra_data_400d019c,0x80,0x40,1);
  }
  while( true ) {
    display_display(iVar2);
    iVar3 = iStack_24;
    memw();
    memw();
    param_1 = *piVar1;
    if (iStack_24 == param_1) break;
    FUN_40082e5c();
LAB_400d2e12:
    uVar4 = (ushort)iVar3;
    FUN_400d4fd8(iVar2,1);
    puVar5 = PTR_str_by_emensta_400d01a0;
    *(undefined4 *)(iVar2 + 0x14) = DAT_400d0194;
    FUN_400d6084(aiStack_34,puVar5);
    if ((uStack_28 & 0x80000000) == 0) {
      if (aiStack_34[0] != 0) {
        uVar4 = (ushort)aiStack_34[2];
      }
    }
    else {
      uVar4 = uStack_28._3_1_ & 0x7f;
    }
    *(short *)(iVar2 + 0x10) = (short)(0x80 - (short)(uVar4 * 6) >> 1);
    *(undefined2 *)(iVar2 + 0x12) = 2;
    (*(code *)PTR_FUN_400d0174)(iVar2,aiStack_34);
    iVar3 = FUN_400910b8(param_1,table_bitmap_refs);
    puVar5 = PTR_bitmap1_data_400d01a8;
    if ((((iVar3 == 0) ||
         (iVar3 = FUN_400910b8(param_1,PTR_str_bitmap2_400d01ac), puVar5 = PTR_bitmap2_data_400d01b0
         , iVar3 == 0)) ||
        (iVar3 = FUN_400910b8(param_1,PTR_str_bitmap3_400d01b4), puVar5 = PTR_bitmap3_data_400d01b8,
        iVar3 == 0)) ||
       (iVar3 = FUN_400910b8(param_1,PTR_str_bitmap4_400d01bc), puVar5 = PTR_bitmap4_data_400d01c0,
       iVar3 == 0)) {
      (*(code *)PTR_FUN_400d01c4)(iVar2,0,0xc,puVar5,0x80,0x32,1);
    }
    FUN_400d5eec(aiStack_34);
  }
  return;
}


