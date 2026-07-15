// 400d2868 statusLedBlink

void statusLedBlink(void)

{
  byte bVar1;
  undefined *puVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  
  iVar4 = FUN_400d670c();
  puVar2 = PTR_DAT_400d00f8;
  bVar1 = *PTR_DAT_400d00f8;
  if (bVar1 == 0) {
    if ((uint)(iVar4 - *DAT_400d00fc) < 0x96) {
      return;
    }
  }
  else {
    uVar6 = 0x96;
    if (*DAT_400d0100 == *(int *)PTR_DAT_400d0104) {
      uVar6 = 1000;
    }
    if ((uint)(iVar4 - *DAT_400d00fc) < uVar6) {
      return;
    }
  }
  *DAT_400d00fc = iVar4;
  *puVar2 = bVar1 ^ 1;
  gpio_write_or_mode(0x1b);
  piVar3 = DAT_400d0100;
  if ((*puVar2 != '\0') &&
     (iVar5 = *DAT_400d0100, iVar4 = *(int *)PTR_DAT_400d0104, *DAT_400d0100 = iVar5 + 1,
     iVar4 < iVar5 + 1)) {
    *piVar3 = 1;
  }
  return;
}


