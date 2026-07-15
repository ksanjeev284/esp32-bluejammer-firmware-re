// 400d5130 FUN_400d5130

void FUN_400d5130(int param_1,byte *param_2,char param_3)

{
  byte bVar1;
  ushort uVar2;
  int iVar3;
  uint uVar4;
  
  if (*(int *)(param_1 + 0x28) == 0) {
    gpio_write_or_mode(*(undefined1 *)(param_1 + 0x35),0);
    while (param_3 = param_3 + -1, param_3 != -1) {
      bVar1 = *param_2;
      if (*(int *)(param_1 + 0x24) == 0) {
        iVar3 = 8;
        uVar4 = 0x80;
        do {
          gpio_write_or_mode(*(undefined1 *)(param_1 + 0x33),bVar1 & uVar4);
          gpio_write_or_mode(*(undefined1 *)(param_1 + 0x34),1);
          gpio_write_or_mode(*(undefined1 *)(param_1 + 0x34),0);
          iVar3 = iVar3 + -1;
          uVar4 = uVar4 >> 1;
        } while (iVar3 != 0);
      }
      else {
        FUN_400d379c(*(int *)(param_1 + 0x24),(uint)bVar1);
      }
      param_2 = param_2 + 1;
    }
  }
  else {
    FUN_400d4b2c(*(int *)(param_1 + 0x28),(int)*(char *)(param_1 + 0x30));
    (**(code **)(**(int **)(param_1 + 0x28) + 8))(*(int **)(param_1 + 0x28),0);
    uVar2 = 1;
    while( true ) {
      param_3 = param_3 + -1;
      if (param_3 == -1) break;
      if (0x7f < uVar2) {
        FUN_400d4b3c(*(undefined4 *)(param_1 + 0x28));
        FUN_400d4b2c(*(undefined4 *)(param_1 + 0x28),(int)*(char *)(param_1 + 0x30));
        (**(code **)(**(int **)(param_1 + 0x28) + 8))(*(int **)(param_1 + 0x28),0);
        uVar2 = 1;
      }
      uVar2 = uVar2 + 1;
      (**(code **)(**(int **)(param_1 + 0x28) + 8))(*(int **)(param_1 + 0x28),*param_2);
      param_2 = param_2 + 1;
    }
    FUN_400d4b3c(*(undefined4 *)(param_1 + 0x28));
  }
  return;
}


