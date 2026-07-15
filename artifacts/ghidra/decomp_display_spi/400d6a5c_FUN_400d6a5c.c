// 400d6a5c FUN_400d6a5c

void FUN_400d6a5c(int param_1,uint param_2,char param_3)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  param_2 = param_2 & 0xff;
  if (2 < param_2) {
    return;
  }
  if (param_1 == 0) {
    return;
  }
  if (param_3 < '\0') {
    param_3 = '\x0f';
    param_2 = 0;
    if ((*(char *)(param_1 + 8) != '\x02') && (param_3 = '\x05', *(char *)(param_1 + 8) != '\x03'))
    {
      param_3 = '\v';
    }
  }
  pinMode((int)param_3,3);
  cVar1 = *(char *)(param_1 + 8);
  if ((cVar1 == '\0') || (cVar1 == '\x01')) {
    uVar2 = 5;
    if ((param_2 != 0) && (uVar2 = 6, param_2 != 1)) {
      uVar2 = 7;
    }
  }
  else {
    if (cVar1 == '\x02') {
      uVar2 = 0xb;
      if (param_2 == 0) goto LAB_400d6ab0;
      uVar3 = 0x3d;
      uVar2 = 0x3e;
    }
    else {
      uVar2 = 0;
      if ((cVar1 != '\x03') || (uVar2 = 0x44, param_2 == 0)) goto LAB_400d6ab0;
      uVar3 = 0x45;
      uVar2 = 0x46;
    }
    if (param_2 == 1) {
      uVar2 = uVar3;
    }
  }
LAB_400d6ab0:
  FUN_400d7c40((int)param_3,uVar2,0);
  FUN_400d6a20(param_1,1 << 0x20 - (0x20 - (param_2 & 0x1f)));
  return;
}


