// 400d69e8 FUN_400d69e8

void FUN_400d69e8(int param_1,char param_2)

{
  if (param_1 != 0) {
    if (param_2 < '\0') {
      param_2 = '\x0f';
      if ((*(char *)(param_1 + 8) != '\x02') && (param_2 = '\x05', *(char *)(param_1 + 8) != '\x03')
         ) {
        param_2 = '\v';
      }
    }
    FUN_400d7c58((int)param_2,0);
    FUN_400d6198((int)param_2,1);
  }
  return;
}


