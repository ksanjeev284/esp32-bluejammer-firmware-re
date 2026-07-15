// 400d32c4 FUN_400d32c4

void FUN_400d32c4(int param_1,char param_2)

{
  if (param_2 == '\0') {
    FUN_400d3034(param_1,1);
    if (*(char *)(param_1 + 0x1b) != '\0') {
      FUN_400d32a0(param_1);
    }
  }
  else {
    FUN_400d3034(param_1,1,0x3f);
  }
  return;
}


