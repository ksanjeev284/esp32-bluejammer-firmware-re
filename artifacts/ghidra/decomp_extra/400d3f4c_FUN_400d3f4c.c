// 400d3f4c FUN_400d3f4c

undefined4 FUN_400d3f4c(undefined4 param_1,uint param_2)

{
  uint uVar1;
  undefined4 uVar2;
  
  uVar1 = FUN_400d3e38();
  uVar2 = 1;
  if ((uVar1 & 1) != (param_2 & 0xff)) {
    if ((param_2 & 0xff) == 0) {
      uVar1 = uVar1 & 0xfffffffe;
    }
    else {
      uVar1 = uVar1 | 1;
    }
    uVar2 = FUN_400d3e5c(uVar1);
  }
  return uVar2;
}


