// 4015e924 FUN_4015e924

void FUN_4015e924(int *param_1,short param_2,short param_3,int param_4,short param_5,short param_6,
                 undefined2 param_7)

{
  int iVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  short sVar5;
  uint uVar6;
  
  iVar1 = (int)param_5;
  (**(code **)(*param_1 + 0x1c))(param_1);
  iVar3 = iVar1 + 7;
  if (iVar1 + 7 < 0) {
    iVar3 = iVar1 + 0xe;
  }
  iVar4 = 0;
  sVar5 = 0;
  cVar2 = '\0';
  while( true ) {
    if (param_6 <= sVar5) break;
    for (uVar6 = 0; (int)uVar6 < iVar1; uVar6 = (uint)(short)((short)uVar6 + 1)) {
      cVar2 = cVar2 << 1;
      if ((uVar6 & 7) == 0) {
        cVar2 = *(char *)(param_4 + iVar4 + ((int)uVar6 >> 3));
      }
      if (cVar2 < '\0') {
        (**(code **)(*param_1 + 0x20))
                  (param_1,(int)(short)((short)uVar6 + param_2),(int)(short)(sVar5 + param_3),
                   param_7);
      }
    }
    sVar5 = sVar5 + 1;
    iVar4 = iVar4 + (iVar3 >> 3);
  }
  (**(code **)(*param_1 + 0x34))(param_1);
  return;
}


