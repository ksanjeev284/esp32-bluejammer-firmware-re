// 400d56b4 display_display

void FUN_400d56b4(int param_1)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  byte *pbVar4;
  ushort uVar5;
  uint uVar6;
  
  if (*(int *)(param_1 + 0x28) == 0) {
    if (*(int *)(param_1 + 0x24) != 0) {
      FUN_400d3730(*(int *)(param_1 + 0x24),*(undefined4 *)(param_1 + 0x44),
                   *(undefined4 *)(param_1 + 0x48));
    }
    gpio_write_or_mode(*(undefined1 *)(param_1 + 0x36),0);
  }
  else {
    FUN_400d4a4c(*(int *)(param_1 + 0x28),*(undefined4 *)(param_1 + 0x38));
  }
  FUN_400d5130(param_1,PTR_DAT_400d0324,5);
  FUN_400d505c(param_1,*(char *)(param_1 + 8) + -1);
  iVar2 = *(short *)(param_1 + 10) + 7;
  if (iVar2 < 0) {
    iVar2 = *(short *)(param_1 + 10) + 0xe;
  }
  pbVar4 = *(byte **)(param_1 + 0x2c);
  uVar3 = (uint)*(ushort *)(param_1 + 8) * (iVar2 >> 3 & 0xffffU) & 0xffff;
  if (*(int *)(param_1 + 0x28) == 0) {
    gpio_write_or_mode(*(undefined1 *)(param_1 + 0x35),1);
    while (uVar3 = uVar3 - 1 & 0xffff, uVar3 != DAT_400d0328) {
      bVar1 = *pbVar4;
      if (*(int *)(param_1 + 0x24) == 0) {
        iVar2 = 8;
        uVar6 = 0x80;
        do {
          gpio_write_or_mode(*(undefined1 *)(param_1 + 0x33),bVar1 & uVar6);
          gpio_write_or_mode(*(undefined1 *)(param_1 + 0x34),1);
          gpio_write_or_mode(*(undefined1 *)(param_1 + 0x34),0);
          iVar2 = iVar2 + -1;
          uVar6 = uVar6 >> 1;
        } while (iVar2 != 0);
      }
      else {
        FUN_400d379c(*(int *)(param_1 + 0x24),(uint)bVar1);
      }
      pbVar4 = pbVar4 + 1;
    }
  }
  else {
    FUN_400d4b2c(*(int *)(param_1 + 0x28),(int)*(char *)(param_1 + 0x30));
    (**(code **)(**(int **)(param_1 + 0x28) + 8))(*(int **)(param_1 + 0x28),0x40);
    uVar6 = DAT_400d0328;
    uVar5 = 1;
    while( true ) {
      uVar3 = uVar3 - 1 & 0xffff;
      if (uVar3 == uVar6) break;
      if (0x7f < uVar5) {
        FUN_400d4b3c(*(undefined4 *)(param_1 + 0x28));
        FUN_400d4b2c(*(undefined4 *)(param_1 + 0x28),(int)*(char *)(param_1 + 0x30));
        (**(code **)(**(int **)(param_1 + 0x28) + 8))(*(int **)(param_1 + 0x28),0x40);
        uVar5 = 1;
      }
      uVar5 = uVar5 + 1;
      (**(code **)(**(int **)(param_1 + 0x28) + 8))(*(int **)(param_1 + 0x28),*pbVar4);
      pbVar4 = pbVar4 + 1;
    }
    FUN_400d4b3c(*(undefined4 *)(param_1 + 0x28));
  }
  if (*(int *)(param_1 + 0x28) == 0) {
    gpio_write_or_mode(*(undefined1 *)(param_1 + 0x36),1);
    if (*(int *)(param_1 + 0x24) != 0) {
      FUN_400d3778();
    }
  }
  else {
    FUN_400d4a4c(*(int *)(param_1 + 0x28),*(undefined4 *)(param_1 + 0x3c));
  }
  return;
}


