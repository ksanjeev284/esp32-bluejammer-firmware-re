// 400d6730 delayMicroseconds

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


