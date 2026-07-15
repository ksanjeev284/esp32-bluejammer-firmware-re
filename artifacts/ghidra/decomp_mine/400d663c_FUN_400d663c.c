// 400d663c FUN_400d663c

undefined4 FUN_400d663c(uint param_1,uint param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  char *pcVar4;
  undefined4 auStack_28 [10];
  
  iVar1 = DAT_400d03b8;
  param_1 = param_1 & 0xff;
  uVar2 = 0x102;
  if (param_1 < 2) {
    pcVar4 = (char *)(DAT_400d03b8 + param_1 * 0xc);
    memw();
    if (*(int *)(pcVar4 + 8) != 0) {
      memw();
      iVar3 = FUN_40094190(*(undefined4 *)(pcVar4 + 8),0xffffffff);
      if (iVar3 == 1) {
        memw();
        uVar2 = 0xffffffff;
        if (*pcVar4 != '\0') {
          memw();
          uVar2 = 0;
          if (*(uint *)(pcVar4 + 4) != param_2) {
            iVar3 = DAT_400d01cc;
            if (param_2 != 0) {
              iVar3 = (param_2 < DAT_400d01e0) * param_2 + (param_2 >= DAT_400d01e0) * DAT_400d01e0;
            }
            auStack_28[0] = DAT_400d03c8;
            if (param_1 != 0) {
              auStack_28[0] = DAT_400d03cc;
            }
            FUN_400e1ba0(auStack_28,iVar3,1);
            uVar2 = DAT_400d03bc;
            memw();
            *(int *)(iVar1 + param_1 * 0xc + 4) = iVar3;
            FUN_400d8bb8(param_1,uVar2);
            uVar2 = 0;
          }
        }
        memw();
        FUN_40093c38(*(undefined4 *)(iVar1 + param_1 * 0xc + 8),0,0);
        return uVar2;
      }
    }
    uVar2 = 0xffffffff;
  }
  return uVar2;
}


