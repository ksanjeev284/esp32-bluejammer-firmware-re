// 400d236c radioTask

void radioTask(void)

{
  char *pcVar1;
  undefined4 uVar2;
  undefined *puVar3;
  undefined4 uVar4;
  undefined1 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  
  FUN_400d36e4(DAT_400d0020);
  FUN_400d6724(2);
  uVar6 = (*(code *)PTR_FUN_400d0084)(0x20);
  FUN_400d35d0(uVar6,2);
  FUN_400d35fc(uVar6,0xe,0xc,0xd,0xf);
  FUN_400d6724(5);
  uVar7 = (*(code *)PTR_FUN_400d0084)(0x20);
  FUN_400d35d0(uVar7,3);
  FUN_400d35fc(uVar7,0x12,0x13,0x17,0x15);
  FUN_400d6724(5);
  uVar2 = DAT_400d0024;
  iVar8 = FUN_400d3448(DAT_400d0024,uVar6);
  puVar3 = PTR_s__________________________________400d002c;
  uVar6 = DAT_400d0028;
  if (iVar8 == 0) {
    FUN_400d5d1c(DAT_400d0028);
    FUN_400d5d30(uVar6,puVar3);
    FUN_400d5d1c(uVar6);
    FUN_400d5d30(uVar6,PTR_DAT_400d0044);
    FUN_400d5d30(uVar6,PTR_DAT_400d0048);
    FUN_400d5d30(uVar6,PTR_DAT_400d004c);
    FUN_400d5d1c(uVar6);
    FUN_400d5d30(uVar6,PTR_str_HSPI_FAIL_400d0050);
  }
  else {
    FUN_400d5d1c(DAT_400d0028);
    FUN_400d5d30(uVar6,puVar3);
    FUN_400d5d1c(uVar6);
    FUN_400d5d30(uVar6,PTR_DAT_400d0030);
    FUN_400d5d30(uVar6,PTR_DAT_400d0034);
    FUN_400d5d30(uVar6,PTR_DAT_400d0038);
    FUN_400d5d1c(uVar6);
    FUN_400d5d30(uVar6,PTR_str_HSPI_SUCCESS_400d003c);
    FUN_400d32c4(uVar2,0);
    FUN_400d3180(uVar2);
    FUN_400d34b0(uVar2,0);
    FUN_400d32f4(uVar2,3,1);
    FUN_400d3328(uVar2,1);
    FUN_400d3460(uVar2,0);
    FUN_400d34d8(uVar2,3,*PTR_DAT_400d0040);
  }
  uVar4 = DAT_400d0054;
  iVar8 = FUN_400d3448(DAT_400d0054,uVar7);
  if (iVar8 == 0) {
    FUN_400d5d1c(uVar6);
    FUN_400d5d30(uVar6,puVar3);
    FUN_400d5d1c(uVar6);
    FUN_400d5d30(uVar6,PTR_DAT_400d006c);
    FUN_400d5d30(uVar6,PTR_DAT_400d0070);
    FUN_400d5d30(uVar6,PTR_DAT_400d0074);
    FUN_400d5d1c(uVar6);
    FUN_400d5d30(uVar6,PTR_str_VSPI_FAIL_400d0078);
    pcVar1 = DAT_400d007c;
  }
  else {
    FUN_400d5d1c(uVar6);
    FUN_400d5d30(uVar6,puVar3);
    FUN_400d5d1c(uVar6);
    FUN_400d5d30(uVar6,PTR_DAT_400d0058);
    FUN_400d5d30(uVar6,PTR_DAT_400d005c);
    FUN_400d5d30(uVar6,PTR_DAT_400d0060);
    FUN_400d5d1c(uVar6);
    FUN_400d5d30(uVar6,PTR_str_VSPI_SUCCESS_400d0064);
    FUN_400d32c4(uVar4,0);
    FUN_400d3180(uVar4);
    FUN_400d34b0(uVar4,0);
    FUN_400d32f4(uVar4,3,1);
    FUN_400d3328(uVar4,1);
    FUN_400d3460(uVar4,0);
    FUN_400d34d8(uVar4,3,*PTR_DAT_400d0068);
    pcVar1 = DAT_400d007c;
  }
  do {
    iVar8 = 100;
    do {
      memw();
      if (*pcVar1 != '\0') {
        FUN_400d3590(uVar2);
        FUN_400d3590(uVar4);
        FUN_400d31d8(uVar2);
        FUN_400d31d8(uVar4);
        while (memw(), *pcVar1 != '\0') {
          FUN_40095724(10);
        }
        FUN_400d31fc(uVar2);
        FUN_400d31fc(uVar4);
        FUN_400d34d8(uVar2,3,*PTR_DAT_400d0040);
        FUN_400d34d8(uVar4,3,*PTR_DAT_400d0068);
      }
      memw();
      iVar9 = *(int *)PTR_DAT_400d0080;
      if (iVar9 == 2) {
        uVar5 = FUN_400d5e80(0x27);
        FUN_400d30d8(uVar2,uVar5);
        uVar6 = 0x27;
LAB_400d26b7:
        uVar5 = FUN_400d5e80(uVar6);
        FUN_400d30d8(uVar4,uVar5);
      }
      else {
        if (2 < iVar9) {
          if (iVar9 == 3) {
            uVar5 = FUN_400d5e80(0xe);
            FUN_400d30d8(uVar2,uVar5);
            uVar6 = 0xe;
          }
          else {
            if (iVar9 != 4) goto LAB_400d2671;
            uVar5 = FUN_400d5e80(0x7d);
            FUN_400d30d8(uVar2,uVar5);
            uVar6 = 0x7d;
          }
          goto LAB_400d26b7;
        }
        if (iVar9 == 1) {
          uVar5 = FUN_400d5e80(0x4f);
          FUN_400d30d8(uVar2,uVar5);
          uVar6 = 0x4f;
          goto LAB_400d26b7;
        }
      }
LAB_400d2671:
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
    FUN_40095724(1);
  } while( true );
}


