// 400d2bfc FUN_400d2bfc size~344

void FUN_400d2bfc(void)

{
  char *pcVar1;
  undefined *puVar2;
  undefined4 uVar3;
  int *piVar4;
  char *pcVar5;
  char *pcVar6;
  int iVar7;
  undefined4 uVar8;
  
  uVar3 = DAT_400d009c;
  FUN_400d380c(DAT_400d009c);
  iVar7 = digitalRead(0);
  pcVar5 = DAT_400d017c;
  piVar4 = DAT_400d0178;
  puVar2 = PTR_DAT_400d0080;
  pcVar1 = DAT_400d007c;
  if (iVar7 == 0) {
    if (*DAT_400d0178 == 0) {
      iVar7 = millis();
      *piVar4 = iVar7;
    }
    else {
      memw();
      if (((*DAT_400d007c == '\0') && (*DAT_400d017c == '\0')) &&
         (iVar7 = millis(), 499 < (uint)(iVar7 - *piVar4))) {
        memw();
        memw();
        *(undefined4 *)PTR_DAT_400d0180 = *(undefined4 *)puVar2;
        memw();
        *(undefined4 *)puVar2 = 0;
        memw();
        *pcVar1 = '\x01';
        *pcVar5 = '\x01';
      }
    }
  }
  else if (*DAT_400d0178 != 0) {
    iVar7 = millis();
    pcVar5 = DAT_400d017c;
    memw();
    if (((uint)(iVar7 - *piVar4) < 500) && (*pcVar1 != '\0')) {
      memw();
      uVar8 = *(undefined4 *)PTR_DAT_400d0180;
      *DAT_400d017c = '\0';
      memw();
      *(undefined4 *)puVar2 = uVar8;
      pcVar6 = DAT_400d0184;
      memw();
      *pcVar1 = '\0';
      *pcVar6 = '\x01';
      *DAT_400d0108 = 0;
      memw();
      iVar7 = *(int *)puVar2;
      if (iVar7 == 2) {
        enterState_BLE();
      }
      else if (iVar7 < 3) {
        if (iVar7 == 1) {
          enterState_BT();
        }
      }
      else if (iVar7 == 3) {
        enterState_WiFi();
      }
      else if (iVar7 == 4) {
        enterState_RC();
      }
    }
    *piVar4 = 0;
    *pcVar5 = '\0';
  }
  memw();
  if ((*pcVar1 == '\0') && (iVar7 = (*(code *)PTR_FUN_400d0188)(uVar3), iVar7 != 0)) {
    if (*DAT_400d0184 == '\0') {
      FUN_400d2844();
    }
    else {
      *DAT_400d0184 = '\0';
    }
  }
  memw();
  iVar7 = *(int *)puVar2;
  if (iVar7 == 2) {
    enterState_BLE();
  }
  else if (iVar7 < 3) {
    if (iVar7 == 0) {
      FUN_400d2a24();
    }
    else if (iVar7 == 1) {
      enterState_BT();
    }
  }
  else if (iVar7 == 3) {
    enterState_WiFi();
  }
  else if (iVar7 == 4) {
    enterState_RC();
  }
  return;
}


