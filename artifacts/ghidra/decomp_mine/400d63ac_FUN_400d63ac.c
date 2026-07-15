// 400d63ac FUN_400d63ac

undefined1 FUN_400d63ac(uint param_1)

{
  undefined1 uVar1;
  
  uVar1 = 0;
  if ((param_1 & 0xff) < 2) {
    memw();
    uVar1 = *(undefined1 *)(DAT_400d03b8 + (param_1 & 0xff) * 0xc);
  }
  return uVar1;
}


