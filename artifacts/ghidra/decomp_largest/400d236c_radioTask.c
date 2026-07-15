// 400d236c radioTask size~908

void radioTask(void)

{
  char *pcVar1;
  undefined4 uVar2;
  undefined *puVar3;
  undefined4 uVar4;
  undefined1 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  
  FUN_400d36e4(DAT_400d0020);
  delay_ms(2);
  uVar6 = (*(code *)PTR_FUN_400d0084)(0x20);
  spi_setBus(uVar6,2);
  spi_setPins(uVar6,0xe,0xc,0xd,0xf);
  delay_ms(5);
  uVar7 = (*(code *)PTR_FUN_400d0084)(0x20);
  spi_setBus(uVar7,3);
  spi_setPins(uVar7,0x12,0x13,0x17,0x15);
  delay_ms(5);
  uVar2 = DAT_400d0024;
  iVar8 = nrf_begin(DAT_400d0024,uVar6);
  puVar3 = PTR_s__________________________________400d002c;
  uVar6 = DAT_400d0028;
  if (iVar8 == 0) {
    Serial_println_empty(DAT_400d0028);
    Serial_print(uVar6,puVar3);
    Serial_println_empty(uVar6);
    Serial_print(uVar6,PTR_DAT_400d0044);
    Serial_print(uVar6,PTR_DAT_400d0048);
    Serial_print(uVar6,PTR_DAT_400d004c);
    Serial_println_empty(uVar6);
    Serial_print(uVar6,PTR_str_HSPI_FAIL_400d0050);
  }
  else {
    Serial_println_empty(DAT_400d0028);
    Serial_print(uVar6,puVar3);
    Serial_println_empty(uVar6);
    Serial_print(uVar6,PTR_DAT_400d0030);
    Serial_print(uVar6,PTR_DAT_400d0034);
    Serial_print(uVar6,PTR_DAT_400d0038);
    Serial_println_empty(uVar6);
    Serial_print(uVar6,PTR_str_HSPI_SUCCESS_400d003c);
    nrf_stopListening(uVar2,0);
    nrf_startListening_or_openPipe(uVar2);
    nrf_setRetries(uVar2,0);
    nrf_setPALevel(uVar2,3,1);
    nrf_setDataRate(uVar2,1);
    nrf_setCRCLength(uVar2,0);
    nrf_startConstCarrier(uVar2,3,*PTR_DAT_400d0040);
  }
  uVar4 = DAT_400d0054;
  iVar8 = nrf_begin(DAT_400d0054,uVar7);
  if (iVar8 == 0) {
    Serial_println_empty(uVar6);
    Serial_print(uVar6,puVar3);
    Serial_println_empty(uVar6);
    Serial_print(uVar6,PTR_DAT_400d006c);
    Serial_print(uVar6,PTR_DAT_400d0070);
    Serial_print(uVar6,PTR_DAT_400d0074);
    Serial_println_empty(uVar6);
    Serial_print(uVar6,PTR_str_VSPI_FAIL_400d0078);
    pcVar1 = DAT_400d007c;
  }
  else {
    Serial_println_empty(uVar6);
    Serial_print(uVar6,puVar3);
    Serial_println_empty(uVar6);
    Serial_print(uVar6,PTR_DAT_400d0058);
    Serial_print(uVar6,PTR_DAT_400d005c);
    Serial_print(uVar6,PTR_DAT_400d0060);
    Serial_println_empty(uVar6);
    Serial_print(uVar6,PTR_str_VSPI_SUCCESS_400d0064);
    nrf_stopListening(uVar4,0);
    nrf_startListening_or_openPipe(uVar4);
    nrf_setRetries(uVar4,0);
    nrf_setPALevel(uVar4,3,1);
    nrf_setDataRate(uVar4,1);
    nrf_setCRCLength(uVar4,0);
    nrf_startConstCarrier(uVar4,3,*PTR_DAT_400d0068);
    pcVar1 = DAT_400d007c;
  }
  do {
    iVar8 = 100;
    do {
      memw();
      if (*pcVar1 != '\0') {
        nrf_stopConstCarrier(uVar2);
        nrf_stopConstCarrier(uVar4);
        nrf_powerDown(uVar2);
        nrf_powerDown(uVar4);
        while (memw(), *pcVar1 != '\0') {
          FUN_40095724(10);
        }
        nrf_powerUp(uVar2);
        nrf_powerUp(uVar4);
        nrf_startConstCarrier(uVar2,3,*PTR_DAT_400d0040);
        nrf_startConstCarrier(uVar4,3,*PTR_DAT_400d0068);
      }
      memw();
      iVar9 = *(int *)PTR_DAT_400d0080;
      if (iVar9 == 2) {
        uVar5 = randomChannel(0x27);
        nrf_setChannel(uVar2,uVar5);
        uVar6 = 0x27;
LAB_400d26b7:
        uVar5 = randomChannel(uVar6);
        nrf_setChannel(uVar4,uVar5);
      }
      else {
        if (2 < iVar9) {
          if (iVar9 == 3) {
            uVar5 = randomChannel(0xe);
            nrf_setChannel(uVar2,uVar5);
            uVar6 = 0xe;
          }
          else {
            if (iVar9 != 4) goto LAB_400d2671;
            uVar5 = randomChannel(0x7d);
            nrf_setChannel(uVar2,uVar5);
            uVar6 = 0x7d;
          }
          goto LAB_400d26b7;
        }
        if (iVar9 == 1) {
          uVar5 = randomChannel(0x4f);
          nrf_setChannel(uVar2,uVar5);
          uVar6 = 0x4f;
          goto LAB_400d26b7;
        }
      }
LAB_400d2671:
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
    FUN_40095724(1);
  } while( true );
}


