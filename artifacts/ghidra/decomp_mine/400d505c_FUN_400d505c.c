// 400d505c FUN_400d505c

void FUN_400d505c(int param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  
  param_2 = param_2 & 0xff;
  if (*(int *)(param_1 + 0x28) == 0) {
    gpio_write_or_mode(*(undefined1 *)(param_1 + 0x35),0);
    if (*(int *)(param_1 + 0x24) == 0) {
      iVar1 = 8;
      uVar2 = 0x80;
      do {
        gpio_write_or_mode(*(undefined1 *)(param_1 + 0x33),param_2 & uVar2);
        gpio_write_or_mode(*(undefined1 *)(param_1 + 0x34),1);
        iVar1 = iVar1 + -1;
        gpio_write_or_mode(*(undefined1 *)(param_1 + 0x34),0);
        uVar2 = uVar2 >> 1;
      } while (iVar1 != 0);
    }
    else {
      FUN_400d379c(*(int *)(param_1 + 0x24),param_2);
    }
  }
  else {
    FUN_400d4b2c(*(int *)(param_1 + 0x28),(int)*(char *)(param_1 + 0x30));
    (**(code **)(**(int **)(param_1 + 0x28) + 8))(*(int **)(param_1 + 0x28),0);
    (**(code **)(**(int **)(param_1 + 0x28) + 8))(*(int **)(param_1 + 0x28),param_2);
    FUN_400d4b3c(*(undefined4 *)(param_1 + 0x28));
  }
  return;
}


