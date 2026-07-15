// 400d2844 FUN_400d2844

void FUN_400d2844(void)

{
  undefined *puVar1;
  
  puVar1 = PTR_DAT_400d0080;
  memw();
  memw();
  *(int *)PTR_DAT_400d0080 = *(int *)PTR_DAT_400d0080 + 1;
  memw();
  if (4 < *(int *)puVar1) {
    memw();
    *(undefined4 *)puVar1 = 1;
  }
  return;
}


