// 400d63d0 FUN_400d63d0

int FUN_400d63d0(uint param_1,char param_2,char param_3,uint param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  int iVar4;
  char *pcVar5;
  undefined4 local_3c;
  int iStack_38;
  int iStack_34;
  undefined2 uStack_30;
  undefined1 auStack_2e [2];
  int iStack_2c;
  
  param_1 = param_1 & 0xff;
  iVar4 = 0x102;
  if (param_1 < 2) {
    iVar4 = DAT_400d03b8 + param_1 * 0xc;
    memw();
    if (*(int *)(iVar4 + 8) == 0) {
      uVar2 = FUN_40093e48(1);
      memw();
      *(undefined4 *)(iVar4 + 8) = uVar2;
      memw();
      if (*(int *)(iVar4 + 8) == 0) {
        return 0x101;
      }
    }
    pcVar5 = (char *)(DAT_400d03b8 + param_1 * 0xc);
    memw();
    iVar1 = FUN_40094190(*(undefined4 *)(pcVar5 + 8),0xffffffff);
    iVar4 = -1;
    if (iVar1 == 1) {
      memw();
      iVar4 = -1;
      if (*pcVar5 == '\0') {
        iVar1 = DAT_400d01cc;
        if (param_4 != 0) {
          iVar1 = (param_4 < DAT_400d01e0) * param_4 + (param_4 >= DAT_400d01e0) * DAT_400d01e0;
        }
        FUN_40090d70(auStack_2e,0,0xe);
        iStack_34 = (int)param_3;
        iStack_38 = (int)param_2;
        local_3c = 1;
        uStack_30 = 0x101;
        iStack_2c = iVar1;
        iVar4 = FUN_400d9204(param_1,&local_3c);
        if ((iVar4 == 0) && (iVar4 = FUN_400d8ca4(param_1,local_3c,0,0,0), iVar4 == 0)) {
          puVar3 = (undefined1 *)(DAT_400d03b8 + param_1 * 0xc);
          memw();
          *puVar3 = 1;
          uVar2 = DAT_400d03bc;
          memw();
          *(int *)(puVar3 + 4) = iVar1;
          FUN_400d8bb8(param_1,uVar2);
        }
        memw();
        FUN_40093c38(*(undefined4 *)(DAT_400d03b8 + param_1 * 0xc + 8),0,0);
      }
    }
  }
  return iVar4;
}


