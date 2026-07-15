// 400d3e38 FUN_400d3e38

undefined4 FUN_400d3e38(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 auStack_24 [9];
  
  uVar2 = 0;
  if ((*DAT_400d0240 != '\0') && (*DAT_400d025c != '\0')) {
    iVar1 = FUN_40126708(auStack_24);
    uVar2 = 0;
    if (iVar1 == 0) {
      uVar2 = auStack_24[0];
    }
  }
  return uVar2;
}


