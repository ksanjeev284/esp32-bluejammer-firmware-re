// 400d3e5c FUN_400d3e5c

bool FUN_400d3e5c(uint param_1)

{
  bool bVar1;
  bool bVar2;
  char *pcVar3;
  byte *pbVar4;
  uint uVar5;
  int iVar6;
  
  uVar5 = FUN_400d3e38();
  pcVar3 = DAT_400d025c;
  if (uVar5 != param_1) {
    bVar1 = uVar5 == 0;
    bVar2 = param_1 != 0;
    if (bVar1 && bVar2) {
      iVar6 = FUN_400d3ce4(*PTR_DAT_400d0260);
      if (iVar6 == 0) {
        return false;
      }
    }
    else if ((uVar5 != 0 || bVar1 && bVar2) && (param_1 == 0 || bVar1 && bVar2)) {
      if (*DAT_400d025c == '\0') {
        return true;
      }
      *DAT_400d025c = bVar1 && bVar2;
      iVar6 = FUN_40126788();
      pbVar4 = DAT_400d0240;
      if (iVar6 == 0) {
        if (*DAT_400d0240 != 0) {
          iVar6 = FUN_400e9ee0();
          *pbVar4 = iVar6 != 0;
        }
        return (bool)(*pbVar4 ^ 1);
      }
      *pcVar3 = '\x01';
      return bVar1 && bVar2;
    }
    pcVar3 = DAT_400d01f8;
    if ((param_1 & 1) != 0) {
      if (*DAT_400d01f8 == '\0') {
        FUN_400d38a0();
      }
      iVar6 = FUN_400d38e8(0,pcVar3);
      if (iVar6 != 0) {
        return false;
      }
    }
    iVar6 = FUN_401266cc(param_1);
    if ((iVar6 != 0) ||
       ((*DAT_400d0264 != '\0' &&
        ((((param_1 & 1) != 0 && (iVar6 = FUN_40126e14(0,8), iVar6 != 0)) ||
         (((param_1 & 2) != 0 && (iVar6 = FUN_40126e14(1,8), iVar6 != 0)))))))) {
      return false;
    }
    pcVar3 = DAT_400d025c;
    if (*DAT_400d025c == '\0') {
      *DAT_400d025c = '\x01';
      iVar6 = FUN_40126730();
      if (iVar6 == 0) {
        return (bool)*pcVar3;
      }
      *pcVar3 = '\0';
      return false;
    }
  }
  return true;
}


