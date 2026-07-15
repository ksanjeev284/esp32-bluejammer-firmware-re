// 400d5220 FUN_400d5220

undefined4 FUN_400d5220(int param_1,undefined1 param_2,char param_3,char param_4,char param_5)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  undefined *puVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  
  if (*(int *)(param_1 + 0x2c) == 0) {
    iVar3 = *(short *)(param_1 + 10) + 7;
    if (iVar3 < 0) {
      iVar3 = *(short *)(param_1 + 10) + 0xe;
    }
    iVar3 = FUN_400987e4((iVar3 >> 3) * (int)*(short *)(param_1 + 8));
    *(int *)(param_1 + 0x2c) = iVar3;
    if (iVar3 == 0) {
      return 0;
    }
  }
  display_clearDisplay(param_1);
  iVar3 = (int)*(short *)(param_1 + 10);
  uVar6 = 0x20;
  if (iVar3 < 0x21) {
    iVar2 = *(short *)(param_1 + 8) + -0x73;
    iVar3 = (iVar3 + -0x20) - (iVar3 + -0x20 >> 0x1f);
    iVar2 = iVar2 - (iVar2 >> 0x1f);
    uVar5 = 0x73;
    puVar4 = PTR_DAT_400d02f8;
  }
  else {
    iVar2 = *(short *)(param_1 + 8) + -0x52;
    iVar3 = (iVar3 + -0x40) - (iVar3 + -0x40 >> 0x1f);
    iVar2 = iVar2 - (iVar2 >> 0x1f);
    uVar6 = 0x40;
    uVar5 = 0x52;
    puVar4 = PTR_DAT_400d02f4;
  }
  (*(code *)PTR_FUN_400d01c4)(param_1,iVar2 >> 1,iVar3 >> 1,puVar4,uVar5,uVar6,1);
  *(undefined1 *)(param_1 + 0x31) = param_2;
  if (*(int *)(param_1 + 0x28) == 0) {
    FUN_400d6198(*(undefined1 *)(param_1 + 0x35),3);
    FUN_400d6198(*(undefined1 *)(param_1 + 0x36),3);
    gpio_write_or_mode(*(undefined1 *)(param_1 + 0x36),1);
    if (*(int *)(param_1 + 0x24) == 0) {
      FUN_400d6198(*(undefined1 *)(param_1 + 0x33),3);
      FUN_400d6198(*(undefined1 *)(param_1 + 0x34),3);
      gpio_write_or_mode(*(undefined1 *)(param_1 + 0x34),0);
    }
    else if (param_5 != '\0') {
      spi_setPins(*(int *)(param_1 + 0x24),0xffffffff,0xffffffff,0xffffffff);
    }
  }
  else {
    if ((param_3 == '\0') && (param_3 = '=', *(short *)(param_1 + 10) == 0x20)) {
      param_3 = '<';
    }
    *(char *)(param_1 + 0x30) = param_3;
    if (param_5 != '\0') {
      FUN_400d493c(*(int *)(param_1 + 0x28),0xffffffff,0xffffffff,0);
    }
  }
  if ((param_4 != '\0') && (-1 < *(char *)(param_1 + 0x37))) {
    FUN_400d6198((int)*(char *)(param_1 + 0x37),3);
    gpio_write_or_mode(*(undefined1 *)(param_1 + 0x37),1);
    delay_ms(1);
    gpio_write_or_mode(*(undefined1 *)(param_1 + 0x37),0);
    delay_ms(10);
    gpio_write_or_mode(*(undefined1 *)(param_1 + 0x37),1);
  }
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
  FUN_400d5130(param_1,PTR_DAT_400d02fc,4);
  FUN_400d505c(param_1,*(char *)(param_1 + 10) + -1);
  FUN_400d5130(param_1,PTR_DAT_400d0300,4);
  uVar6 = 0x14;
  if (*(char *)(param_1 + 0x31) == '\x01') {
    uVar6 = 0x10;
  }
  FUN_400d505c(param_1,uVar6);
  FUN_400d5130(param_1,PTR_DAT_400d0304,4);
  *(undefined1 *)(param_1 + 0x40) = 0x8f;
  iVar3 = *(int *)(param_1 + 8);
  uVar6 = 2;
  if (iVar3 != DAT_400d0308) {
    if (iVar3 == DAT_400d030c) {
      uVar1 = 0xcf;
      if (*(char *)(param_1 + 0x31) == '\x01') {
        uVar1 = 0x9f;
      }
      *(undefined1 *)(param_1 + 0x40) = uVar1;
      uVar6 = 0x12;
    }
    else if (iVar3 == DAT_400d0310) {
      uVar1 = 0xaf;
      if (*(char *)(param_1 + 0x31) == '\x01') {
        uVar1 = 0x10;
      }
      *(undefined1 *)(param_1 + 0x40) = uVar1;
    }
  }
  FUN_400d505c(param_1,0xda);
  FUN_400d505c(param_1,uVar6);
  FUN_400d505c(param_1,0x81);
  FUN_400d505c(param_1,*(undefined1 *)(param_1 + 0x40));
  FUN_400d505c(param_1,0xd9);
  uVar6 = 0x22;
  if (*(char *)(param_1 + 0x31) != '\x01') {
    uVar6 = 0xf1;
  }
  FUN_400d505c(param_1,uVar6);
  FUN_400d5130(param_1,DAT_400d0314,6);
  if (*(int *)(param_1 + 0x28) == 0) {
    gpio_write_or_mode(*(undefined1 *)(param_1 + 0x36),1);
    if (*(int *)(param_1 + 0x24) != 0) {
      FUN_400d3778();
    }
  }
  else {
    FUN_400d4a4c(*(int *)(param_1 + 0x28),*(undefined4 *)(param_1 + 0x3c));
  }
  return 1;
}


