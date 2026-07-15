// 400d35fc spi_setPins

void spi_setPins(char *param_1,byte param_2,byte param_3,byte param_4,byte param_5)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  char cVar4;
  
  if (*(int *)(param_1 + 4) == 0) {
    if (*(int *)(param_1 + 0x10) == 0) {
      uVar2 = FUN_400d7038(*(undefined4 *)(param_1 + 0x14));
      *(undefined4 *)(param_1 + 0x10) = uVar2;
    }
    iVar3 = FUN_400d6d08(*param_1,*(undefined4 *)(param_1 + 0x10),0,1);
    *(int *)(param_1 + 4) = iVar3;
    if (iVar3 != 0) {
      if ((param_4 & param_5 & param_3 & param_2) == 0xff) {
        cVar1 = *param_1;
        cVar4 = '\x12';
        if (cVar1 != '\x03') {
          cVar4 = '\x0e';
        }
        param_1[9] = cVar4;
        cVar4 = '\x13';
        if (cVar1 != '\x03') {
          cVar4 = '\f';
        }
        param_1[10] = cVar4;
        cVar4 = '\x17';
        if (cVar1 != '\x03') {
          cVar4 = '\r';
        }
        param_1[0xb] = cVar4;
        cVar4 = '\x0f';
        if (cVar1 == '\x03') {
          cVar4 = '\x05';
        }
        param_1[0xc] = cVar4;
      }
      else {
        param_1[9] = param_2;
        param_1[10] = param_3;
        param_1[0xb] = param_4;
        param_1[0xc] = param_5;
      }
      FUN_400d680c(iVar3,(int)param_1[9]);
      FUN_400d6860(*(undefined4 *)(param_1 + 4),(int)param_1[10]);
      FUN_400d68cc(*(undefined4 *)(param_1 + 4),(int)param_1[0xb]);
    }
  }
  return;
}


