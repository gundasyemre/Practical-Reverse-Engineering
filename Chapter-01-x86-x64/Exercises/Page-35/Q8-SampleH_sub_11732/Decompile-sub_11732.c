psmth __usercustom sub_11732(psmth result , DWORD outptr1, DWORD outptr2, int targetValue) //returns pointer to something and uses custom calling convention
{
    pmsth var1;
    
    switch( targetValue )
    {
        case 1:
            var1 = *(DWORD *)(result + 0x3C) >> 1;
            result += 0x40;
            break;
        case 2 :
            var1 = *(DWORD *)( result + 0X3C)  >> 1;
            result += 0x44;
            break;
        case 3:
            var1 = *(DWORD *)(result + 0x3C) >> 1;
            result += 0x5E
            break;
        case 12:
            var1 = *(DWORD *)(result + 0X3C) >> 1;
            result += 0XC;
            break;
        default:
            return result;
    }
    *outptr2 = var1 ;
    *outptr1 = result;
    return result;
}