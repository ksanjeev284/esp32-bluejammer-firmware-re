// 400d3060 nrf_flushRx

undefined1 FUN_400d3060(int param_1)

{
  nrf_writeCmd(param_1,0xe2,0);
  return *(undefined1 *)(param_1 + 0xc);
}


