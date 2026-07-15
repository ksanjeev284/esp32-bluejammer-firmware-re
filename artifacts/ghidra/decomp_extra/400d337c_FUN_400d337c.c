// 400d337c FUN_400d337c

bool FUN_400d337c(int param_1)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  
  delay_ms(5);
  FUN_400d3034(param_1,4,0x5f);
  FUN_400d3328(param_1,0);
  iVar2 = FUN_400d2fcc(param_1,0x1d);
  FUN_400d327c(param_1);
  iVar3 = FUN_400d2fcc(param_1,0x1d);
  *(bool *)(param_1 + 0x19) = iVar2 == iVar3;
  if (iVar3 != 0) {
    if (iVar2 == iVar3) {
      FUN_400d327c(param_1);
    }
    FUN_400d3034(param_1,0x1d,0);
  }
  *(undefined1 *)(param_1 + 0x1b) = 0;
  FUN_400d3034(param_1,0x1c,0);
  *(undefined1 *)(param_1 + 0x1d) = 0;
  FUN_400d3034(param_1,1,0x3f);
  FUN_400d3034(param_1,2,3);
  FUN_400d30f0(param_1,0x20);
  FUN_400d3248(param_1,5);
  nrf_setChannel(param_1,0x4c);
  FUN_400d3034(param_1,7,0x70);
  FUN_400d3060(param_1);
  FUN_400d3078(param_1);
  FUN_400d3034(param_1,0,0xc);
  uVar1 = FUN_400d2fcc(param_1,0);
  *(undefined1 *)(param_1 + 0x18) = uVar1;
  FUN_400d31fc(param_1);
  return *(char *)(param_1 + 0x18) == '\x0e';
}


