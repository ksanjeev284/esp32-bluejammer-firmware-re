// 400d3328 FUN_400d3328

bool FUN_400d3328(int param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = FUN_400d2fcc(param_1,6);
  if (param_2 == 2) {
    *(undefined4 *)(param_1 + 0x20) = 0x1f9;
    uVar2 = 0x20;
  }
  else if (param_2 == 1) {
    *(undefined4 *)(param_1 + 0x20) = 0xf0;
    uVar2 = 8;
  }
  else {
    *(undefined4 *)(param_1 + 0x20) = 0x118;
    uVar2 = 0;
  }
  uVar2 = uVar1 & 0xd7 | uVar2;
  FUN_400d3034(param_1,6,uVar2);
  uVar1 = FUN_400d2fcc(param_1,6);
  return uVar2 == uVar1;
}


