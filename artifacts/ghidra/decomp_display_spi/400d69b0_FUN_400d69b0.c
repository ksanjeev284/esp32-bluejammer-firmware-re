// 400d69b0 FUN_400d69b0

void FUN_400d69b0(int param_1,char param_2)

{
  if (param_1 != 0) {
    if (param_2 < '\0') {
      param_2 = '\r';
      if ((*(char *)(param_1 + 8) != '\x02') && (param_2 = '\x17', *(char *)(param_1 + 8) != '\x03')
         ) {
        param_2 = '\b';
      }
    }
    FUN_400d7c58((int)param_2,0);
    pinMode((int)param_2,1);
  }
  return;
}


