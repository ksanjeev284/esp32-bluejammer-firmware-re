// 400d379c FUN_400d379c

undefined4 FUN_400d379c(int param_1,undefined1 param_2)

{
  undefined4 uVar1;
  
  if (*(char *)(param_1 + 0x18) == '\0') {
    uVar1 = FUN_400d6e80(*(undefined4 *)(param_1 + 4),param_2);
  }
  else {
    uVar1 = FUN_400d6fd8();
  }
  return uVar1;
}


