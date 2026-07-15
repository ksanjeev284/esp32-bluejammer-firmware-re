# Additional findings pass

## `FUN_400d2844` @ `400d2844`
```c

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


```


## `statusLedBlink` @ `400d2868`
```c

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


```


## `FUN_400d2f0c` @ `400d2f0c`
```c

void FUN_400d2f0c(void)

{
  FUN_400d5014(DAT_400d0144,0x80,0x40,DAT_400d018c,0xffffffff,DAT_400d01c8,DAT_400d01cc);
  return;
}


```


## `FUN_400d2f2c` @ `400d2f2c`
```c

void FUN_400d2f2c(void)

{
  FUN_400d4fec(DAT_400d0144);
  return;
}


```


## `FUN_400d3090` @ `400d3090`
```c

void FUN_400d3090(undefined4 *param_1)

{
  uint uVar1;
  
  uVar1 = DAT_400d01d0;
  *param_1 = DAT_400d0020;
  if ((uint)param_1[2] <= uVar1) {
    param_1[2] = DAT_400d01d4;
  }
  return;
}


```


## `FUN_400d31d8` @ `400d31d8`
```c

void FUN_400d31d8(int param_1)

{
  FUN_400d2f4c(param_1,0);
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfd;
  FUN_400d3034(param_1,0);
  return;
}


```


## `FUN_400d31fc` @ `400d31fc`
```c

void FUN_400d31fc(int param_1)

{
  if ((*(byte *)(param_1 + 0x18) & 2) == 0) {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) | 2;
    FUN_400d3034(param_1);
    FUN_400d6730(DAT_400d01dc);
  }
  return;
}


```


## `FUN_400d3220` @ `400d3220`
```c

void FUN_400d3220(undefined4 param_1)

{
  FUN_400d2f4c(param_1,0);
  FUN_400d3034(param_1,7,0x10);
  FUN_400d2f90(param_1,0xe3,0);
  FUN_400d2f4c(param_1,1);
  return;
}


```


## `FUN_400d3248` @ `400d3248`
```c

void FUN_400d3248(int param_1,char param_2)

{
  byte bVar1;
  
  if ((byte)(param_2 - 2U) == 0) {
    FUN_400d3034(param_1,3);
    *(undefined1 *)(param_1 + 0x1c) = 2;
  }
  else {
    bVar1 = param_2 - 2U & 3;
    FUN_400d3034(param_1,3,bVar1);
    *(byte *)(param_1 + 0x1c) = bVar1 + 2;
  }
  return;
}


```


## `FUN_400d327c` @ `400d327c`
```c

void FUN_400d327c(undefined4 *param_1)

{
  undefined1 uVar1;
  
  FUN_400d2f60(param_1);
  uVar1 = FUN_400d379c(*param_1,0x50);
  *(undefined1 *)(param_1 + 3) = uVar1;
  FUN_400d379c(*param_1,0x73);
  FUN_400d2f7c(param_1);
  return;
}


```


## `FUN_400d32a0` @ `400d32a0`
```c

void FUN_400d32a0(int param_1)

{
  uint uVar1;
  
  if (*(char *)(param_1 + 0x1b) != '\0') {
    uVar1 = FUN_400d2fcc(param_1,0x1d);
    FUN_400d3034(param_1,0x1d,uVar1 & 0xfd);
    *(undefined1 *)(param_1 + 0x1b) = 0;
  }
  return;
}


```


## `FUN_400d3494` @ `400d3494`
```c

void FUN_400d3494(int param_1)

{
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xf7;
  FUN_400d3034(param_1,0);
  return;
}


```


## `FUN_400d3590` @ `400d3590`
```c

void FUN_400d3590(int param_1)

{
  uint uVar1;
  
  FUN_400d31d8(param_1);
  uVar1 = FUN_400d2fcc(param_1,6);
  FUN_400d3034(param_1,6,uVar1 & 0x6f);
  FUN_400d2f4c(param_1,0);
  FUN_400d3078(param_1);
  if (*(char *)(param_1 + 0x19) != '\0') {
    FUN_400d2ff8(param_1,0x10,param_1 + 0x13,*(undefined1 *)(param_1 + 0x1c));
  }
  return;
}


```


## `FUN_400d36a4` @ `400d36a4`
```c

void FUN_400d36a4(int param_1,char param_2)

{
  if (param_2 == '\0') {
    if (*(char *)(param_1 + 8) != '\0') {
      FUN_400d6b3c(*(undefined4 *)(param_1 + 4));
      FUN_400d69e8(*(undefined4 *)(param_1 + 4),(int)*(char *)(param_1 + 0xc));
    }
  }
  else if (*(char *)(param_1 + 8) == '\0') {
    FUN_400d6a5c(*(undefined4 *)(param_1 + 4),0,(int)*(char *)(param_1 + 0xc));
    FUN_400d6af8(*(undefined4 *)(param_1 + 4));
  }
  *(char *)(param_1 + 8) = param_2;
  return;
}


```


## `FUN_400d37d8` @ `400d37d8`
```c

void FUN_400d37d8(uint *param_1,uint param_2)

{
  uint uVar1;
  
  *param_1 = param_2;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  FUN_400d6198(param_2 & 0xff,5);
  uVar1 = FUN_400d6224((char)*param_1);
  param_1[4] = uVar1;
  uVar1 = FUN_400d6224((char)*param_1);
  param_1[5] = uVar1;
  uVar1 = FUN_400d6224((char)*param_1);
  param_1[6] = uVar1;
  param_1[8] = 0;
  return;
}


```


## `FUN_400d380c` @ `400d380c`
```c

void FUN_400d380c(undefined1 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  iVar1 = FUN_400d6224(*param_1);
  *(int *)(param_1 + 0x1c) = iVar1;
  if (*(int *)(param_1 + 0x18) != iVar1) {
    uVar2 = FUN_400d670c();
    *(undefined4 *)(param_1 + 0x20) = uVar2;
    *(undefined4 *)(param_1 + 0x18) = *(undefined4 *)(param_1 + 0x1c);
  }
  iVar1 = FUN_400d670c();
  if (*(uint *)(param_1 + 4) <= (uint)(iVar1 - *(int *)(param_1 + 0x20))) {
    *(undefined4 *)(param_1 + 0x10) = *(undefined4 *)(param_1 + 0x14);
    *(undefined4 *)(param_1 + 0x14) = *(undefined4 *)(param_1 + 0x1c);
  }
  iVar1 = *(int *)(param_1 + 0x10);
  iVar4 = *(int *)(param_1 + 0x14);
  if (iVar1 == iVar4) {
    return;
  }
  iVar3 = *(int *)(param_1 + 0xc);
  if (iVar3 != 2) {
    if (iVar3 == 0) {
      if (iVar1 != 1) {
        return;
      }
      if (iVar4 != 0) {
        return;
      }
    }
    else {
      if (iVar3 != 1 || iVar1 != 0) {
        return;
      }
      if (iVar4 != 1) {
        return;
      }
    }
  }
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 1;
  return;
}


```


## `FUN_400d4fd8` @ `400d4fd8`
```c

void FUN_400d4fd8(undefined4 param_1,undefined1 param_2)

{
  (*(code *)PTR_FUN_400d02ec)(param_1,param_2,param_2);
  return;
}


```


## `FUN_400d51fc` @ `400d51fc`
```c

void FUN_400d51fc(int param_1)

{
  int iVar1;
  
  iVar1 = *(short *)(param_1 + 10) + 7;
  if (iVar1 < 0) {
    iVar1 = *(short *)(param_1 + 10) + 0xe;
  }
  FUN_40090d70(*(undefined4 *)(param_1 + 0x2c),0,(iVar1 >> 3) * (int)*(short *)(param_1 + 8));
  return;
}


```


## `FUN_400d56b4` @ `400d56b4`
```c

void FUN_400d56b4(int param_1)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  byte *pbVar4;
  ushort uVar5;
  uint uVar6;
  
  if (*(int *)(param_1 + 0x28) == 0) {
    if (*(int *)(param_1 + 0x24) != 0) {
      FUN_400d3730(*(int *)(param_1 + 0x24),*(undefined4 *)(param_1 + 0x44),
                   *(undefined4 *)(param_1 + 0x48));
    }
    gpio_write_or_mode(*(undefined1 *)(param_1 + 0x36),0);
  }
  else {
    FUN_400d4a4c(*(int *)(param_1 + 0x28),*(undefined4 *)(param_1 + 0x38));
  }
  FUN_400d5130(param_1,PTR_DAT_400d0324,5);
  FUN_400d505c(param_1,*(char *)(param_1 + 8) + -1);
  iVar2 = *(short *)(param_1 + 10) + 7;
  if (iVar2 < 0) {
    iVar2 = *(short *)(param_1 + 10) + 0xe;
  }
  pbVar4 = *(byte **)(param_1 + 0x2c);
  uVar3 = (uint)*(ushort *)(param_1 + 8) * (iVar2 >> 3 & 0xffffU) & 0xffff;
  if (*(int *)(param_1 + 0x28) == 0) {
    gpio_write_or_mode(*(undefined1 *)(param_1 + 0x35),1);
    while (uVar3 = uVar3 - 1 & 0xffff, uVar3 != DAT_400d0328) {
      bVar1 = *pbVar4;
      if (*(int *)(param_1 + 0x24) == 0) {
        iVar2 = 8;
        uVar6 = 0x80;
        do {
          gpio_write_or_mode(*(undefined1 *)(param_1 + 0x33),bVar1 & uVar6);
          gpio_write_or_mode(*(undefined1 *)(param_1 + 0x34),1);
          gpio_write_or_mode(*(undefined1 *)(param_1 + 0x34),0);
          iVar2 = iVar2 + -1;
          uVar6 = uVar6 >> 1;
        } while (iVar2 != 0);
      }
      else {
        FUN_400d379c(*(int *)(param_1 + 0x24),(uint)bVar1);
      }
      pbVar4 = pbVar4 + 1;
    }
  }
  else {
    FUN_400d4b2c(*(int *)(param_1 + 0x28),(int)*(char *)(param_1 + 0x30));
    (**(code **)(**(int **)(param_1 + 0x28) + 8))(*(int **)(param_1 + 0x28),0x40);
    uVar6 = DAT_400d0328;
    uVar5 = 1;
    while( true ) {
      uVar3 = uVar3 - 1 & 0xffff;
      if (uVar3 == uVar6) break;
      if (0x7f < uVar5) {
        FUN_400d4b3c(*(undefined4 *)(param_1 + 0x28));
        FUN_400d4b2c(*(undefined4 *)(param_1 + 0x28),(int)*(char *)(param_1 + 0x30));
        (**(code **)(**(int **)(param_1 + 0x28) + 8))(*(int **)(param_1 + 0x28),0x40);
        uVar5 = 1;
      }
      uVar5 = uVar5 + 1;
      (**(code **)(**(int **)(param_1 + 0x28) + 8))(*(int **)(param_1 + 0x28),*pbVar4);
      pbVar4 = pbVar4 + 1;
    }
    FUN_400d4b3c(*(undefined4 *)(param_1 + 0x28));
  }
  if (*(int *)(param_1 + 0x28) == 0) {
    gpio_write_or_mode(*(undefined1 *)(param_1 + 0x36),1);
    if (*(int *)(param_1 + 0x24) != 0) {
      FUN_400d3778();
    }
  }
  else {
    FUN_400d4a4c(*(int *)(param_1 + 0x28),*(undefined4 *)(param_1 + 0x3c));
  }
  return;
}


```


## `FUN_400d6084` @ `400d6084`
```c

void FUN_400d6084(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  
  FUN_400d5eb4(param_1);
  if (param_2 != 0) {
    uVar1 = FUN_400912e8(param_2);
    FUN_400d604c(param_1,param_2,uVar1);
  }
  return;
}


```


## `FUN_400d6100` @ `400d6100`
```c

undefined4 FUN_400d6100(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (param_2 != 0) {
    uVar1 = FUN_400912e8(param_2);
    uVar1 = FUN_400d60a0(param_1,param_2,uVar1);
  }
  return uVar1;
}


```


## `FUN_400d5eec` @ `400d5eec`
```c

void FUN_400d5eec(undefined4 param_1)

{
  FUN_400d5ed4(param_1);
  return;
}


```


## `FUN_400d670c` @ `400d670c`
```c

undefined4 FUN_400d670c(void)

{
  undefined4 uVar1;
  undefined8 uVar2;
  
  uVar2 = FUN_40084928();
  uVar1 = (*DAT_400d03d4)((int)uVar2,(int)((ulonglong)uVar2 >> 0x20),DAT_400d03d0,DAT_400d038c);
  return uVar1;
}


```


## `FUN_400d6224` @ `400d6224`
```c

undefined4 FUN_400d6224(undefined1 param_1)

{
  undefined4 uVar1;
  
  uVar1 = FUN_400d84b4(param_1);
  return uVar1;
}


```


## `FUN_400d83d0` @ `400d83d0`
```c

undefined4 FUN_400d83d0(uint param_1,int param_2)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  
  uVar1 = (*DAT_400d0394)(DAT_400d0380,DAT_400d055c,param_1);
  if ((uVar1 & 1) == 0) {
    uVar2 = FUN_40098600();
    memw();
    FUN_40100120(1,PTR_DAT_400d0518,PTR_s_E___u___s___s__d____s_400d051c,uVar2,PTR_DAT_400d0518,
                 PTR_s_gpio_set_level_400d0598,0xe2,PTR_s_GPIO_output_gpio_num_error_400d0564);
    uVar2 = 0x102;
  }
  else {
    iVar3 = **(int **)PTR_PTR_400d0530;
    if (param_2 == 0) {
      if (0x1f < (int)param_1) {
        memw();
        memw();
        memw();
        memw();
        memw();
        memw();
        *(uint *)(iVar3 + 0x18) =
             *(uint *)(iVar3 + 0x18) & 0xffffff00 | 1 << 0x20 - (0x20 - (param_1 & 0x1f)) & 0xffU;
        memw();
        return 0;
      }
      memw();
      *(int *)(iVar3 + 0xc) = 1 << 0x20 - (0x20 - (param_1 & 0x1f));
      memw();
    }
    else if ((int)param_1 < 0x20) {
      memw();
      *(int *)(iVar3 + 8) = 1 << 0x20 - (0x20 - (param_1 & 0x1f));
    }
    else {
      memw();
      memw();
      memw();
      memw();
      memw();
      memw();
      *(uint *)(iVar3 + 0x14) =
           *(uint *)(iVar3 + 0x14) & 0xffffff00 | 1 << 0x20 - (0x20 - (param_1 & 0x1f)) & 0xffU;
      memw();
    }
    uVar2 = 0;
    memw();
  }
  return uVar2;
}


```


## `FUN_400d6730` @ `400d6730`
```c

/* WARNING: Removing unreachable block (ram,0x400d676d) */
/* WARNING: Removing unreachable block (ram,0x400d674e) */
/* WARNING: Removing unreachable block (ram,0x400d675a) */

void FUN_400d6730(uint param_1)

{
  ulonglong uVar1;
  ulonglong uVar2;
  
  uVar1 = FUN_40084928();
  if (param_1 != 0) {
    if (uVar1 + param_1 < uVar1) {
      do {
        uVar2 = FUN_40084928();
      } while (uVar1 + param_1 < uVar2);
    }
    do {
      uVar2 = FUN_40084928();
    } while (uVar2 < uVar1 + param_1);
  }
  return;
}


```


## `FUN_400d3060` @ `400d3060`
```c

undefined1 FUN_400d3060(int param_1)

{
  FUN_400d2f90(param_1,0xe2,0);
  return *(undefined1 *)(param_1 + 0xc);
}


```


## `FUN_400d3078` @ `400d3078`
```c

undefined1 FUN_400d3078(int param_1)

{
  FUN_400d2f90(param_1,0xe1,0);
  return *(undefined1 *)(param_1 + 0xc);
}


```


## `FUN_400d30f0` @ `400d30f0`
```c

void FUN_400d30f0(int param_1,byte param_2)

{
  int iVar1;
  int iVar2;
  char cVar3;
  
  cVar3 = '\x01';
  if (param_2 != 0) {
    cVar3 = (param_2 < 0x20) * param_2 + (param_2 >= 0x20) * ' ';
  }
  *(char *)(param_1 + 0xd) = cVar3;
  iVar1 = 0x11;
  do {
    iVar2 = iVar1 + 1;
    FUN_400d3034(param_1,iVar1,*(undefined1 *)(param_1 + 0xd));
    iVar1 = iVar2;
  } while (iVar2 != 0x17);
  return;
}


```


## `nrf_isChipConnected` @ `400d3120`
```c

bool nrf_isChipConnected(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_400d2fcc(param_1,3);
  return *(byte *)(param_1 + 0x1c) - 2 == iVar1;
}


```


## `FUN_400d337c` @ `400d337c`
```c

bool FUN_400d337c(int param_1)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  
  delay_ms(5);
  FUN_400d3034(param_1,4,0x5f);
  FUN_400d3328(param_1,0);
  iVar2 = FUN_400d2fcc(param_1,0x1d);
  FUN_400d327c(param_1);
  iVar3 = FUN_400d2fcc(param_1,0x1d);
  *(bool *)(param_1 + 0x19) = iVar2 == iVar3;
  if (iVar3 != 0) {
    if (iVar2 == iVar3) {
      FUN_400d327c(param_1);
    }
    FUN_400d3034(param_1,0x1d,0);
  }
  *(undefined1 *)(param_1 + 0x1b) = 0;
  FUN_400d3034(param_1,0x1c,0);
  *(undefined1 *)(param_1 + 0x1d) = 0;
  FUN_400d3034(param_1,1,0x3f);
  FUN_400d3034(param_1,2,3);
  FUN_400d30f0(param_1,0x20);
  FUN_400d3248(param_1,5);
  nrf_setChannel(param_1,0x4c);
  FUN_400d3034(param_1,7,0x70);
  FUN_400d3060(param_1);
  FUN_400d3078(param_1);
  FUN_400d3034(param_1,0,0xc);
  uVar1 = FUN_400d2fcc(param_1,0);
  *(undefined1 *)(param_1 + 0x18) = uVar1;
  FUN_400d31fc(param_1);
  return *(char *)(param_1 + 0x18) == '\x0e';
}


```


## `nrf_begin` @ `400d3448`
```c

undefined4 nrf_begin(undefined4 *param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  *param_1 = param_2;
  iVar1 = FUN_400d3144(param_1);
  uVar2 = 0;
  if (iVar1 != 0) {
    uVar2 = FUN_400d337c(param_1);
  }
  return uVar2;
}


```


## `nrf_startConstCarrier` @ `400d34d8`
```c

void nrf_startConstCarrier(int param_1,undefined1 param_2,undefined1 param_3)

{
  int *piVar1;
  byte bVar2;
  undefined1 local_44 [32];
  int iStack_24;
  
  piVar1 = DAT_400d0130;
  memw();
  iStack_24 = *DAT_400d0130;
  memw();
  FUN_400d3180(param_1);
  bVar2 = FUN_400d2fcc(param_1,6);
  FUN_400d3034(param_1,6,bVar2 | 0x90);
  if (*(char *)(param_1 + 0x19) != '\0') {
    FUN_400d32c4(param_1,0);
    FUN_400d3034(param_1,4,0);
    local_44[0] = 0xff;
    FUN_400d2ff8(param_1,0x10,local_44,5);
    FUN_400d3078(param_1);
    FUN_400d2ff8(param_1,0xa0,local_44,0x20);
    FUN_400d3494(param_1);
  }
  FUN_400d32f4(param_1,param_2,1);
  nrf_setChannel(param_1,param_3);
  FUN_400d2f4c(param_1,1);
  if (*(char *)(param_1 + 0x19) != '\0') {
    delay_ms(1);
    FUN_400d3220(param_1);
  }
  memw();
  memw();
  if (iStack_24 != *piVar1) {
    FUN_40082e5c();
  }
  return;
}


```


## `FUN_400d32f4` @ `400d32f4`
```c

void FUN_400d32f4(undefined4 param_1,byte param_2,char param_3)

{
  byte bVar1;
  
  bVar1 = FUN_400d2fcc(param_1,6);
  FUN_400d3034(param_1,6,
               bVar1 & 0xf8 | param_3 + ((param_2 < 3) * param_2 + (param_2 >= 3) * '\x03') * '\x02'
              );
  return;
}


```


## `FUN_400d3328` @ `400d3328`
```c

bool FUN_400d3328(int param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = FUN_400d2fcc(param_1,6);
  if (param_2 == 2) {
    *(undefined4 *)(param_1 + 0x20) = 0x1f9;
    uVar2 = 0x20;
  }
  else if (param_2 == 1) {
    *(undefined4 *)(param_1 + 0x20) = 0xf0;
    uVar2 = 8;
  }
  else {
    *(undefined4 *)(param_1 + 0x20) = 0x118;
    uVar2 = 0;
  }
  uVar2 = uVar1 & 0xd7 | uVar2;
  FUN_400d3034(param_1,6,uVar2);
  uVar1 = FUN_400d2fcc(param_1,6);
  return uVar2 == uVar1;
}


```


## `FUN_400d3460` @ `400d3460`
```c

void FUN_400d3460(int param_1,int param_2)

{
  byte bVar1;
  byte bVar2;
  
  bVar2 = *(byte *)(param_1 + 0x18) & 0xf3;
  if (param_2 != 0) {
    if (param_2 == 1) {
      bVar1 = 8;
    }
    else {
      bVar1 = 0xc;
    }
    bVar2 = bVar2 | bVar1;
  }
  *(byte *)(param_1 + 0x18) = bVar2;
  FUN_400d3034(param_1,0,*(undefined1 *)(param_1 + 0x18));
  return;
}


```


## `FUN_400d34b0` @ `400d34b0`
```c

void FUN_400d34b0(undefined4 param_1,byte param_2,byte param_3)

{
  FUN_400d3034(param_1,4,
               ((param_2 < 0xf) * param_2 + (param_2 >= 0xf) * '\x0f') * '\x10' |
               (param_3 < 0xf) * param_3 + (param_3 >= 0xf) * '\x0f');
  return;
}


```


## `FUN_400d32c4` @ `400d32c4`
```c

void FUN_400d32c4(int param_1,char param_2)

{
  if (param_2 == '\0') {
    FUN_400d3034(param_1,1);
    if (*(char *)(param_1 + 0x1b) != '\0') {
      FUN_400d32a0(param_1);
    }
  }
  else {
    FUN_400d3034(param_1,1,0x3f);
  }
  return;
}


```


## `FUN_400d3180` @ `400d3180`
```c

void FUN_400d3180(int param_1)

{
  byte bVar1;
  
  FUN_400d2f4c(param_1,0);
  FUN_400d6730(*(undefined4 *)(param_1 + 0x20));
  if (*(char *)(param_1 + 0x1b) != '\0') {
    FUN_400d3078(param_1);
  }
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfe;
  FUN_400d3034(param_1,0);
  FUN_400d2ff8(param_1,10,param_1 + 0x13,*(undefined1 *)(param_1 + 0x1c));
  bVar1 = FUN_400d2fcc(param_1,2);
  FUN_400d3034(param_1,2,bVar1 | 1);
  return;
}


```


## String xref function map
### S1
- 400d28eb PARAM enterState_BT
- 400d010c DATA ?
### S2
- 400d2933 PARAM enterState_BLE
- 400d0114 DATA ?
### S3
- 400d297b PARAM enterState_WiFi
- 400d011c DATA ?
### S4
- 400d29c3 PARAM enterState_RC
- 400d0124 DATA ?
### S0
- 400d2a47 PARAM FUN_400d2a24
- 400d2a5f PARAM FUN_400d2a24
- 400d013c DATA ?
### Connected
- 400d2b71 PARAM FUN_400d2a24
- 400d0164 DATA ?
### emensta
- 400d01a0 DATA ?
### SSD1306fail
- 400d0190 DATA ?

## Callers of nrf_setChannel / randomChannel
### target 400d30d8
- 400d3404 in FUN_400d337c@400d337c
- 400d3564 in nrf_startConstCarrier@400d34d8
- 400d2699 in radioTask@400d236c
- 400d26b2 in radioTask@400d236c
- 400d26c5 in radioTask@400d236c
- 400d26dd in radioTask@400d236c
- 400d26f5 in radioTask@400d236c
### target 400d5e80
- 400d5e79 in FUN_400d5e70@400d5e70
- 400d268d in radioTask@400d236c
- 400d26a7 in radioTask@400d236c
- 400d26ba in radioTask@400d236c
- 400d26d2 in radioTask@400d236c
- 400d26ea in radioTask@400d236c
### target 400d34d8
- 400d2489 in radioTask@400d236c
- 400d2539 in radioTask@400d236c
- 400d264d in radioTask@400d236c
- 400d265d in radioTask@400d236c
### target 400d3448
- 400d23de in radioTask@400d236c
- 400d2496 in radioTask@400d236c

## Memory blocks
- DROM 3f400020-3f41cfcf size=118704
- DRAM1 3ffbdb60-3ffc0b9f size=12352
- DRAM2 3ffc0ba0-3ffc3b17 size=12152
- IRAM 40080000-4009a277 size=107128
- IROM 400d0020-4016907f size=626784
