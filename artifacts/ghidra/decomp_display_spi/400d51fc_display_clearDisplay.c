// 400d51fc display_clearDisplay

void display_clearDisplay(int param_1)

{
  int iVar1;
  
  iVar1 = *(short *)(param_1 + 10) + 7;
  if (iVar1 < 0) {
    iVar1 = *(short *)(param_1 + 10) + 0xe;
  }
  FUN_40090d70(*(undefined4 *)(param_1 + 0x2c),0,(iVar1 >> 3) * (int)*(short *)(param_1 + 8));
  return;
}


