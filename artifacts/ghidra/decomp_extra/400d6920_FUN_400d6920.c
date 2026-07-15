// 400d6920 FUN_400d6920

void FUN_400d6920(int param_1,char param_2)

{
  if (param_1 != 0) {
    if (param_2 < '\0') {
      param_2 = '\x0e';
      if ((*(char *)(param_1 + 8) != '\x02') && (param_2 = '\x12', *(char *)(param_1 + 8) != '\x03')
         ) {
        param_2 = '\x06';
      }
    }
    FUN_400d7c58((int)param_2,0);
    FUN_400d6198((int)param_2,1);
  }
  return;
}


