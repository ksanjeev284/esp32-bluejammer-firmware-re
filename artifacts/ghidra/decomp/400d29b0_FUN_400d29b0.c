// 400d29b0 FUN_400d29b0

void FUN_400d29b0(void)

{
  int *piVar1;
  undefined *puVar2;
  undefined4 uVar3;
  
  piVar1 = DAT_400d0108;
  if (*DAT_400d0108 != 4) {
    FUN_400d5d30(DAT_400d0028,PTR_str_State4_RC_400d0124);
    puVar2 = PTR_str_bitmap4_400d0128;
    *piVar1 = 4;
    FUN_400d2dac(puVar2,0);
    uVar3 = FUN_400d670c();
    *DAT_400d00fc = uVar3;
    *DAT_400d0100 = 0;
    *PTR_DAT_400d00f8 = 0;
    FUN_400d6214(0x1b);
    *(undefined4 *)PTR_DAT_400d0104 = 4;
  }
  FUN_400d2868();
  return;
}


