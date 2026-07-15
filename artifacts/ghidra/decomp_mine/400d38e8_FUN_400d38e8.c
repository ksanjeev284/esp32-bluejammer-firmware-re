// 400d38e8 FUN_400d38e8

undefined4 FUN_400d38e8(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = 0xffffffff;
  if (param_1 < 3) {
    uVar1 = FUN_400e4ef4(*(undefined4 *)(DAT_400d0200 + param_1 * 4),param_2);
  }
  return uVar1;
}


