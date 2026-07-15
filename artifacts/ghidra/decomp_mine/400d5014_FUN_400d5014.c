// 400d5014 FUN_400d5014

void FUN_400d5014(undefined4 *param_1,undefined1 param_2,undefined1 param_3,int param_4,
                 undefined1 param_5,undefined4 param_6,undefined4 param_7)

{
  undefined4 uVar1;
  
  FUN_400d4b7c(param_1,param_2,param_3);
  *param_1 = PTR_PTR_400d02f0;
  param_1[9] = 0;
  if (param_4 == 0) {
    param_4 = DAT_400d018c;
  }
  param_1[10] = param_4;
  *(undefined1 *)((int)param_1 + 0x33) = 0xff;
  *(undefined2 *)(param_1 + 0xd) = 0xffff;
  *(undefined1 *)((int)param_1 + 0x36) = 0xff;
  param_1[0xb] = 0;
  param_1[0xf] = param_7;
  uVar1 = DAT_400d01e0;
  *(undefined1 *)((int)param_1 + 0x37) = param_5;
  param_1[0x11] = uVar1;
  param_1[0xe] = param_6;
  *(undefined2 *)(param_1 + 0x12) = 1;
  return;
}


