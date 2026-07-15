// 400d3078 nrf_flushTx

undefined1 FUN_400d3078(int param_1)

{
  nrf_writeCmd(param_1,0xe1,0);
  return *(undefined1 *)(param_1 + 0xc);
}


