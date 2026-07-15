// 400d3ce4 FUN_400d3ce4

char FUN_400d3ce4(char param_1)

{
  undefined4 *puVar1;
  int *piVar2;
  char cVar3;
  int iVar4;
  char *pcVar5;
  undefined *puStack_188;
  undefined *puStack_184;
  undefined1 auStack_180 [108];
  undefined4 uStack_114;
  undefined4 uStack_110;
  undefined4 uStack_10c;
  undefined4 uStack_108;
  undefined4 uStack_104;
  undefined4 uStack_100;
  undefined4 uStack_fc;
  undefined4 uStack_f8;
  undefined4 uStack_f4;
  undefined4 uStack_ec;
  undefined4 uStack_e4;
  undefined4 uStack_dc;
  undefined4 uStack_d8;
  undefined4 uStack_d0;
  undefined4 uStack_cc;
  undefined4 uStack_c4;
  undefined4 uStack_c0;
  undefined4 auStack_b4 [36];
  char *pcStack_24;
  
  pcVar5 = DAT_400d0240;
  puVar1 = DAT_400d0130;
  memw();
  pcStack_24 = (char *)*DAT_400d0130;
  memw();
  if (*DAT_400d0240 != '\0') goto LAB_400d3e00;
  *DAT_400d0240 = '\x01';
  iVar4 = FUN_400d3b94();
  cVar3 = '\0';
  if (iVar4 != 0) goto LAB_400d3d29;
  do {
    *pcVar5 = '\0';
    while( true ) {
      memw();
      memw();
      pcVar5 = (char *)*puVar1;
      if (pcStack_24 == pcVar5) {
        return cVar3;
      }
      FUN_40082e5c();
LAB_400d3d29:
      piVar2 = DAT_400d0200;
      if (DAT_400d0200[1] == 0) {
        iVar4 = FUN_400ea328();
        piVar2[1] = iVar4;
      }
      if (*piVar2 == 0) {
        iVar4 = FUN_400ea360();
        *piVar2 = iVar4;
      }
      FUN_40090d70(&uStack_10c,0,0x54);
      uStack_e4 = 6;
      uStack_dc = 0x2f0;
      puStack_188 = PTR_FUN_400d0244;
      uStack_c4 = 7;
      puStack_184 = PTR_DAT_400d0248;
      uStack_c0 = DAT_400d024c;
      uStack_114 = 8;
      uStack_108 = 8;
      uStack_100 = 0x10;
      uStack_110 = 0x20;
      uStack_fc = 1;
      uStack_f8 = 1;
      uStack_f4 = 1;
      uStack_ec = 1;
      uStack_d8 = 0x20;
      FUN_40090c10(auStack_180,PTR_DAT_400d0250,0x6c);
      uStack_cc = *(undefined4 *)(PTR_DAT_400d0254 + 4);
      uStack_d0 = *(undefined4 *)PTR_DAT_400d0254;
      if (*DAT_400d0258 == '\0') {
        uStack_10c = 1;
        uStack_104 = 0x20;
        uStack_100 = 4;
        uStack_114 = 4;
        uStack_108 = 0;
      }
      iVar4 = FUN_400e9f40(&puStack_188);
      if (iVar4 != 0) break;
      if (param_1 == '\0') {
        iVar4 = FUN_40126f20(1);
        if (iVar4 == 0) {
          param_1 = '\x01';
        }
        *pcVar5 = param_1;
      }
      if (*pcVar5 != '\0') {
        auStack_b4[0] = 0;
        FUN_400d3908(auStack_b4);
      }
LAB_400d3e00:
      cVar3 = *pcVar5;
    }
  } while( true );
}


