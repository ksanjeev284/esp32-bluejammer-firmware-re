// 400d34b0 nrf_setRetries

void FUN_400d34b0(undefined4 param_1,byte param_2,byte param_3)

{
  nrf_writeRegister(param_1,4,
                    ((param_2 < 0xf) * param_2 + (param_2 >= 0xf) * '\x0f') * '\x10' |
                    (param_3 < 0xf) * param_3 + (param_3 >= 0xf) * '\x0f');
  return;
}


