// 400d2d68 FUN_400d2d68

void FUN_400d2d68(void)

{
  int iVar1;
  int iVar2;
  
  FUN_400d493c(DAT_400d018c,4,5,0);
  iVar1 = DAT_400d0144;
  iVar2 = FUN_400d5220(DAT_400d0144,2,0x3c,1);
  if (iVar2 == 0) {
    Serial_print(DAT_400d0028,PTR_str_SSD1306_alloc_failed_400d0190);
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  FUN_400d51fc(iVar1);
  *(undefined4 *)(iVar1 + 0x14) = DAT_400d0194;
  FUN_400d56b4(iVar1);
  return;
}


