// 400d2f4c FUN_400d2f4c

void FUN_400d2f4c(int param_1,undefined1 param_2)

{
  if (*(char *)(param_1 + 5) != *(char *)(param_1 + 4)) {
    gpio_write_or_mode(*(char *)(param_1 + 4),param_2);
  }
  return;
}


