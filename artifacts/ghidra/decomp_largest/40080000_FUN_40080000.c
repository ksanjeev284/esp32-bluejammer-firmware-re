// 40080000 FUN_40080000 size~15

void FUN_40080000(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  undefined4 unaff_retaddr;
  
  *(undefined4 *)(param_4 + -0x10) = unaff_retaddr;
  *(BADSPACEBASE **)(param_4 + -0xc) = register0x00000004;
  *(undefined4 *)(param_4 + -8) = param_1;
  *(undefined4 *)(param_4 + -4) = param_2;
  rfwo();
  return;
}


