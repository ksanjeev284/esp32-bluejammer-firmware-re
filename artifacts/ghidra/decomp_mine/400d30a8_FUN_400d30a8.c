// 400d30a8 FUN_400d30a8

void FUN_400d30a8(int param_1,undefined1 param_2,undefined1 param_3,undefined4 param_4)

{
  *(undefined1 *)(param_1 + 0xd) = 0x20;
  *(undefined1 *)(param_1 + 0x19) = 0;
  *(undefined1 *)(param_1 + 0x1a) = 0;
  *(undefined1 *)(param_1 + 0x1e) = 0;
  *(undefined1 *)(param_1 + 4) = param_2;
  *(undefined1 *)(param_1 + 5) = param_3;
  *(undefined4 *)(param_1 + 8) = param_4;
  *(undefined2 *)(param_1 + 0x1c) = 0x105;
  *(undefined4 *)(param_1 + 0x24) = 5;
  FUN_400d3090(param_1);
  return;
}


