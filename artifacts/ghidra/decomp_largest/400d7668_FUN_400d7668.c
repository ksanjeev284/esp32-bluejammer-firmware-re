// 400d7668 FUN_400d7668 size~327

undefined *
FUN_400d7668(uint param_1,uint param_2,uint param_3,byte param_4,char param_5,undefined2 param_6,
            undefined2 param_7,char param_8,undefined1 param_9)

{
  undefined *puVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  undefined *puVar6;
  int *in_t0;
  undefined4 uStack_3c;
  uint uStack_38;
  uint uStack_34;
  uint uStack_30;
  undefined4 uStack_2c;
  undefined1 uStack_28;
  undefined4 uStack_24;
  
  param_1 = param_1 & 0xff;
  if (param_1 < 3) {
    puVar1 = PTR_DAT_400d04a8 + param_1 * 0xc;
    iVar2 = FUN_400dc0dc(param_1);
    if (iVar2 != 0) {
      FUN_400d73d4(puVar1);
    }
    piVar3 = (int *)(PTR_DAT_400d04a8 + param_1 * 0xc);
    if (*piVar3 == 0) goto LAB_400d7729;
    do {
      piVar3 = in_t0;
      puVar4 = (undefined4 *)(PTR_DAT_400d04a8 + param_1 * 0xc);
      do {
        iVar2 = FUN_40094190(*puVar4,0xffffffff);
      } while (iVar2 != 1);
      uStack_38 = param_3 >> 2 & 3;
      uStack_34 = param_3 & 3;
      uStack_30 = param_3 >> 4 & 3;
      uStack_2c = 0;
      uStack_28 = param_9;
      uStack_24 = 0;
      uStack_3c = FUN_400d7338(param_2);
      iVar2 = FUN_400dbe78(param_1,param_6,param_7,0x14,PTR_DAT_400d04a8 + param_1 * 0xc + 8,0);
      if (iVar2 == 0) {
        iVar2 = FUN_400db570(param_1,&uStack_3c);
        if (iVar2 == 0) {
          iVar2 = FUN_400db2b0(param_1,(int)param_5,(int)(char)param_4,0xffffffff);
          param_2 = (uint)param_4;
          if (iVar2 == 0) {
            if ((param_8 == '\0') || (iVar2 = FUN_400dae78(param_1,0x24), iVar2 == 0)) {
              FUN_40093c38(*(undefined4 *)(PTR_DAT_400d04a8 + param_1 * 0xc),0,0);
              FUN_400d7658(puVar1);
              return puVar1;
            }
            uVar5 = 0xdc;
            puVar6 = PTR_s_uart_set_line_inverse_uart_nr__U_400d04bc;
          }
          else {
            uVar5 = 0xd7;
            puVar6 = PTR_s_uart_set_pin_uart_nr__txPin__rxP_400d04b8;
          }
        }
        else {
          uVar5 = 0xd6;
          puVar6 = PTR_s_uart_param_config_uart_nr___uart_400d04b4;
        }
      }
      else {
        uVar5 = 0xd5;
        puVar6 = PTR_s_uart_driver_install_uart_nr__rx__400d04ac;
      }
      FUN_4009317c(iVar2,PTR_s_C__Users_emens_AppData_Local_Ard_400d04a4,uVar5,
                   PTR_s_uartBegin_400d04b0,puVar6);
      param_3 = 0;
      in_t0 = piVar3;
LAB_400d7729:
      iVar2 = FUN_40093e48(1);
      *piVar3 = iVar2;
    } while (iVar2 != 0);
  }
  return (undefined *)0x0;
}


