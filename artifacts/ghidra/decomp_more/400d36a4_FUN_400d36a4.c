// 400d36a4 FUN_400d36a4

void FUN_400d36a4(int param_1,char param_2)

{
  if (param_2 == '\0') {
    if (*(char *)(param_1 + 8) != '\0') {
      FUN_400d6b3c(*(undefined4 *)(param_1 + 4));
      FUN_400d69e8(*(undefined4 *)(param_1 + 4),(int)*(char *)(param_1 + 0xc));
    }
  }
  else if (*(char *)(param_1 + 8) == '\0') {
    FUN_400d6a5c(*(undefined4 *)(param_1 + 4),0,(int)*(char *)(param_1 + 0xc));
    FUN_400d6af8(*(undefined4 *)(param_1 + 4));
  }
  *(char *)(param_1 + 8) = param_2;
  return;
}


