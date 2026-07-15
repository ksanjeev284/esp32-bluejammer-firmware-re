// 400d2714 FUN_400d2714

void FUN_400d2714(void)

{
  undefined4 uVar1;
  undefined *puVar2;
  
  FUN_400d3e5c(0);
  FUN_400d6150();
  uVar1 = DAT_400d0028;
  FUN_400d5ac4(DAT_400d0028,DAT_400d0094,DAT_400d0090,0xffffffff,0xffffffff,0,DAT_400d0098,0x70);
  (*(code *)PTR_FUN_400d00f4)(DAT_400d009c,0x32);
  FUN_400d6198(0x1b,3);
  FUN_400d2d68();
  FUN_400d6198(0,5);
  FUN_400d2dac(PTR_str_bitmapboot_400d00a0,1);
  delay_ms(2000);
  puVar2 = PTR_s__________________________________400d00a4;
  Serial_print(uVar1,PTR_s__________________________________400d00a4);
  Serial_println_empty(uVar1);
  Serial_print(uVar1,PTR_DAT_400d00a8);
  Serial_print(uVar1,PTR_DAT_400d00ac);
  Serial_print(uVar1,PTR_DAT_400d00b0);
  Serial_print(uVar1,PTR_DAT_400d00b4);
  Serial_print(uVar1,PTR_DAT_400d00b8);
  Serial_println_empty(uVar1);
  Serial_print(uVar1,puVar2);
  Serial_println_empty(uVar1);
  Serial_print(uVar1,PTR_str_Firmware_Banner_400d00bc);
  Serial_println_empty(uVar1);
  Serial_print(uVar1,PTR_DAT_400d00c0);
  Serial_print(uVar1,PTR_DAT_400d00c4);
  Serial_print(uVar1,PTR_DAT_400d00c8);
  Serial_print(uVar1,PTR_DAT_400d00cc);
  Serial_print(uVar1,PTR_DAT_400d00d0);
  Serial_print(uVar1,PTR_DAT_400d00d4);
  Serial_println_empty(uVar1);
  Serial_print(uVar1,puVar2);
  Serial_println_empty(uVar1);
  Serial_print(uVar1,PTR_str_Educational_400d00d8);
  Serial_println_empty(uVar1);
  Serial_print(uVar1,PTR_str_GitHub_URL_400d00dc);
  Serial_println_empty(uVar1);
  Serial_print(uVar1,PTR_str_Disclaimer_400d00e0);
  Serial_println_empty(uVar1);
  Serial_print(uVar1,puVar2);
  FUN_400949f4(ptr_radioTask_fn,ptr_RadioTask_name,DAT_400d00e8,0,1,DAT_400d00e4,0);
  return;
}


