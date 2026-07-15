// 400d636c FUN_400d636c

undefined4 FUN_400d636c(uint param_1)

{
  undefined4 uVar1;
  undefined *puVar2;
  
  uVar1 = 0x102;
  if ((param_1 & 0xff) < 2) {
    puVar2 = PTR_DAT_400d03b4 + (param_1 & 0xff) * 0x30;
    uVar1 = 0x101;
    if (*(int *)(puVar2 + 0x2c) != 0) {
      FUN_40094190(*(int *)(puVar2 + 0x2c),0xffffffff);
      FUN_400d6260(puVar2);
      uVar1 = 0;
      if (*(int *)(puVar2 + 0x2c) != 0) {
        FUN_40093c38(*(int *)(puVar2 + 0x2c),0,0,0);
        uVar1 = 0;
      }
    }
  }
  return uVar1;
}


