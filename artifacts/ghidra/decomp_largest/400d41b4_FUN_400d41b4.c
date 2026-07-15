// 400d41b4 FUN_400d41b4 size~734

void FUN_400d41b4(int *param_1)

{
  int *piVar1;
  int *piVar2;
  byte bVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  int aiStack_188 [45];
  int iStack_d4;
  undefined1 auStack_d0 [4];
  code *pcStack_cc;
  undefined1 auStack_c8 [8];
  int iStack_c0;
  code *pcStack_bc;
  code *pcStack_b8;
  int iStack_b4;
  undefined1 auStack_b0 [140];
  int iStack_24;
  
  piVar1 = DAT_400d0130;
  memw();
  iStack_24 = *DAT_400d0130;
  memw();
  if (param_1 == (int *)0x0) goto LAB_400d446d;
  iVar5 = *param_1;
  if (iVar5 == 1) {
    FUN_400d4840();
  }
  else if (iVar5 == 2) {
    FUN_400d4528(6);
    FUN_400d3e08(8);
    FUN_40126dd0(*(undefined4 *)PTR_DAT_400d0288);
  }
  else {
    if (iVar5 == 3) {
      FUN_400d4528(0xff);
      uVar6 = 0x78;
      goto LAB_400d426c;
    }
    if (iVar5 == 4) {
      FUN_400d4528(0);
      uVar6 = 0x10;
    }
    else {
      if (iVar5 == 5) {
        bVar3 = *(byte *)((int)param_1 + 0x2b);
        if (bVar3 == 0) {
          bVar3 = 1;
LAB_400d42b2:
          uVar6 = 5;
          if ((bVar3 & 0xfb) == 200) goto LAB_400d42c5;
          if (bVar3 != 2) {
            uVar6 = 6;
            goto LAB_400d42c5;
          }
        }
        else {
          uVar6 = 1;
          if ((bVar3 != 0xc9) && ((bVar3 != 0xca || (uVar6 = 4, *PTR_DAT_400d028c != '\0'))))
          goto LAB_400d42b2;
LAB_400d42c5:
          FUN_400d4528(uVar6);
        }
        FUN_400d3e20(0x70);
        uVar6 = DAT_400d01e8;
        if (bVar3 != 8) {
          if (*PTR_DAT_400d028c == '\0') {
            iVar5 = FUN_400d4834(DAT_400d01e8);
            if ((iVar5 == 0) || (iVar5 = (*(code *)PTR_FUN_400d0298)(bVar3), iVar5 == 0)) {
              if (bVar3 == 0xcb) {
                FUN_400d4528(4);
              }
              goto LAB_400d41d4;
            }
          }
          else {
            *PTR_DAT_400d028c = 0;
          }
          FUN_400d47a4(uVar6,0);
          FUN_400d46f4(uVar6);
        }
        goto LAB_400d41d4;
      }
      if (iVar5 == 7) {
        FUN_400d4528(3);
        uVar6 = 0x30;
      }
      else {
        if (iVar5 == 9) {
          FUN_400d4528(0);
          uVar6 = 0x20;
LAB_400d426c:
          FUN_400d3e20(uVar6);
          goto LAB_400d41d4;
        }
        uVar6 = 1;
        if (iVar5 != 10) {
          uVar6 = 5;
          if (iVar5 == 0xb) goto LAB_400d426c;
          uVar6 = 4;
          if (iVar5 != 0xc) {
            if (iVar5 == 0xd) {
              iVar5 = FUN_40126d78(aiStack_188);
              if ((iVar5 == 0) && (iStack_d4 != 0)) goto LAB_400d41d4;
              uVar6 = 4;
              goto LAB_400d426c;
            }
            uVar6 = 0x80;
            if (iVar5 != 0x12) {
              uVar6 = 0x780;
              if (iVar5 == 0x13) goto LAB_400d426c;
              uVar6 = 0x100;
              if (iVar5 != 0x14) {
                if (iVar5 == 0x15) {
                  uVar6 = 0x700;
                  goto LAB_400d426c;
                }
                uVar6 = 0x300;
                if (((iVar5 != 0x16) && (uVar6 = 0x50, iVar5 != 8)) && (uVar6 = 2, iVar5 != 0x10)) {
                  if (iVar5 != 0x17) {
                    if (iVar5 == 0x1f) {
                      iVar5 = 0;
                      if ((char)param_1[0x19] != '\0') {
                        iVar5 = (int)param_1 + 0x65;
                      }
                      FUN_400d46a0(DAT_400d01e8,param_1 + 1,param_1 + 9,0,iVar5,1);
                    }
                    else if (iVar5 == 0x20) {
                      FUN_400e9af4(2);
                      *DAT_400d0290 = 1;
                    }
                    goto LAB_400d41d4;
                  }
                  uVar6 = 0x500;
                }
              }
            }
          }
        }
      }
    }
    FUN_400d3e08(uVar6);
  }
LAB_400d41d4:
  piVar2 = DAT_400d0294;
  for (uVar4 = 0; iVar5 = *piVar2, uVar4 < (uint)(piVar2[1] - iVar5 >> 5); uVar4 = uVar4 + 1) {
    FUN_400d4194(auStack_d0,iVar5 + uVar4 * 0x20);
    if (((pcStack_cc != (code *)0x0) || (iStack_c0 != 0)) || (pcStack_b8 != (code *)0x0)) {
      if ((iStack_b4 == 0x28) || (iStack_b4 == *param_1)) {
        if (pcStack_cc == (code *)0x0) {
          if (iStack_c0 == 0) {
            (*pcStack_b8)(param_1);
          }
          else {
            aiStack_188[0] = *param_1;
            FUN_40090c10(auStack_b0,param_1 + 1,0x8c);
            (*pcStack_bc)(auStack_c8,aiStack_188,auStack_b0);
          }
        }
        else {
          (*pcStack_cc)();
        }
      }
    }
    (*(code *)PTR_FUN_400d0284)(auStack_c8);
  }
LAB_400d446d:
  memw();
  memw();
  if (iStack_24 != *piVar1) {
    FUN_40082e5c();
    (*(code *)PTR_FUN_400d0284)(auStack_c8);
    (*(code *)PTR_FUN_400d008c)(0);
  }
  return;
}


