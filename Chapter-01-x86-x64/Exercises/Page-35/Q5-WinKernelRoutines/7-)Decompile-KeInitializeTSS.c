int KiInitializeTRTSS(int arg1 , int arg2){
    if (a2 != 0)
    {
        *(arg2+4) &= 0X0FFF0FFFF;
        *(arg2) = 8363;
    }

    memset(*(a1+0x88), 255 , 0x2004);
    memset(*(arg1+0x68), 0 , 0x20);
    *(arg1+0x68) = 4;
    *(arg1+0x6B) = 0x1818;

    memset(*(arg1 + 0x208C),0 , 0x20);
    *(arg1+0x208C) = 4;
    *(arg1 + 0x208F) = 0x1818;
    *(arg1 + 0x60) = 0;
    *(arg1 + 0x64) = 0x20AC0000;
    *(arg1 + 0x8) = 0x10;
    return 0x10;
}