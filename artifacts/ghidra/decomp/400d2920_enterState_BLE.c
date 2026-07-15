// 400d2920 enterState_BLE

void enterState_BLE(void)

{
  int *piVar1;
  undefined *puVar2;
  undefined4 uVar3;
  
  piVar1 = DAT_400d0108;
  if (*DAT_400d0108 != 2) {
    Serial_print(DAT_400d0028,PTR_str_State2_BLE_400d0114);
    puVar2 = PTR_str_bitmap2_400d0118;
    *piVar1 = 2;
    FUN_400d2dac(puVar2,0);
    uVar3 = FUN_400d670c();
    *DAT_400d00fc = uVar3;
    *DAT_400d0100 = 0;
    *PTR_DAT_400d00f8 = 0;
    gpio_write_or_mode(0x1b);
    *(undefined4 *)PTR_DAT_400d0104 = 2;
  }
  statusLedBlink();
  return;
}


