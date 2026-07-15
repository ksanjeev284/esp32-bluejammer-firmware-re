// 40082f0c ESP32_IMAGE_ENTRY size~559

void ESP32_IMAGE_ENTRY(void)

{
  byte bVar1;
  byte bVar2;
  undefined *puVar3;
  undefined *puVar4;
  uint *puVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  uint uVar9;
  byte *pbVar10;
  undefined1 in_PRID;
  undefined8 uVar11;
  byte bStack_39;
  undefined1 auStack_38 [10];
  byte bStack_2e;
  
  FUN_400967f4(PTR_LAB_4008062c);
  iVar6 = (*DAT_40080690)(0);
  (*DAT_40080690)(1);
  FUN_40090d70(DAT_40080660,0,DAT_4008065c - DAT_40080660);
  if (iVar6 != 5) {
    FUN_40090d70(DAT_40080668,0,DAT_40080664 - DAT_40080668);
  }
  iVar7 = (*(code *)PTR_FUN_40080694)();
  if (iVar7 != 0) {
    FUN_40082e3c();
  }
  FUN_40090078();
  (*(code *)PTR_FUN_40080698)();
  FUN_40090080();
  (*(code *)PTR_FUN_40080648)();
  pbVar10 = DAT_40080634;
  memw();
  *DAT_40080634 = 1;
  memw();
  (*(code *)PTR_FUN_4008069c)(auStack_38);
  puVar3 = PTR_DAT_40080518;
  if (bStack_2e < 2) {
    pbVar10 = PTR_DAT_40080518;
    if (*(int *)PTR_DAT_40080518 != 0) {
      uVar8 = FUN_40098600();
      puVar4 = PTR_s_cpu_start_4008066c;
      (*DAT_40080524)(PTR_s_E___u___s__Running_on_single_cor_40080670,uVar8,PTR_s_cpu_start_4008066c
                     );
      pbVar10 = *(byte **)puVar3;
      if (pbVar10 != (byte *)0x0) {
        uVar8 = FUN_40098600();
        (*DAT_40080524)(PTR_s_E___u___s__Check_that_CONFIG_FRE_40080674,uVar8,puVar4);
      }
    }
    FUN_40098648();
  }
  FUN_4008cb4c();
  (*DAT_400804b8)(1);
  FUN_4008cbb0();
  FUN_4008cb4c();
  (*DAT_40080598)(1);
  FUN_4008cbb0();
  FUN_400840fc(1);
  puVar5 = DAT_40080678;
  uVar9 = FUN_40084444(DAT_40080678);
  if ((uVar9 & 1) == 0) {
    uVar9 = FUN_40084444(puVar5);
    memw();
    *puVar5 = uVar9 | 1;
    puVar5 = DAT_4008067c;
    memw();
    uVar9 = FUN_40084444(DAT_4008067c);
    memw();
    *puVar5 = uVar9 & 0xfffffffe;
    puVar5 = DAT_40080680;
    memw();
    uVar9 = FUN_40084444(DAT_40080680);
    memw();
    *puVar5 = uVar9 | 1;
    memw();
    uVar9 = FUN_40084444(puVar5);
    memw();
    *puVar5 = uVar9 & 0xfffffffe;
  }
  memw();
  (*DAT_40080644)(PTR_LAB_40080684);
  do {
    memw();
    bVar1 = *pbVar10;
    memw();
    bVar2 = pbVar10[1];
    (*DAT_4008057c)(100);
  } while ((bVar2 & bVar1) == 0);
  (*(code *)PTR_FUN_400806a0)();
  (*(code *)PTR_FUN_400806a4)();
  uVar11 = (*(code *)PTR_FUN_400806a8)();
  *DAT_40080688 = uVar11;
  memw();
  (*(code *)PTR_FUN_40080654)();
  uVar8 = FUN_40091fa0();
  FUN_40083a88(0);
  FUN_40083acc(0,uVar8,DAT_4008068c);
  if (iVar6 == 5) {
    (*(code *)PTR_FUN_400806ac)();
  }
  (*(code *)PTR_FUN_40080658)();
  FUN_40090d70(auStack_38,0,0x18);
  FUN_40090c10(auStack_38,DAT_400804a4,0x18);
  FUN_4008ccf8(auStack_38);
  FUN_4008cd38(auStack_38);
  FUN_4008cf14(auStack_38);
  FUN_4008cc84();
  pbVar10 = DAT_40080638;
  memw();
  *DAT_40080638 = 1;
  memw();
  bStack_39 = 0;
  while (memw(), bStack_39 == 0) {
    memw();
    memw();
    memw();
    memw();
    memw();
    memw();
    bStack_39 = *pbVar10 & 1 & pbVar10[1];
    memw();
    memw();
    (*DAT_4008057c)(100);
  }
  uVar9 = rsr(in_PRID);
  memw();
  (**(code **)(PTR_PTR_40080640 + (uVar9 >> 0xd & 1) * 4))();
  return;
}


