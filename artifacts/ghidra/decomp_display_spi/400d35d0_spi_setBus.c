// 400d35d0 spi_setBus

void spi_setBus(undefined1 *param_1,undefined1 param_2)

{
  undefined4 uVar1;
  
  *(undefined4 *)(param_1 + 8) = 0xffffff00;
  param_1[0xc] = 0xff;
  uVar1 = DAT_400d01e0;
  *param_1 = param_2;
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *(undefined4 *)(param_1 + 0x14) = uVar1;
  param_1[0x18] = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  uVar1 = FUN_40093e48(1);
  *(undefined4 *)(param_1 + 0x1c) = uVar1;
  return;
}


