NTSTATUS RtlValidateUnicodeString ( ULONG Flags , PCUNICODE_STRING String){
    if (Flags != 0 )
    {
        return 0x0c00000D;
    }
    return RtlUnicodeStringValidateWorker(String);
}


NTSTATUS RtlUnicodeStringValidateWorker(PCUNICODE_STRING SourceString , const size_t cchMax , ULONG dwFlags){

    if (SourceString == NUL){
        return 0x00000000 ; // STATUS_SUCCESS
    }

    USHORT length = SourceString->Length;
    USHORT maxLength = SourceString -> MaximumLength;

    if ( (length & 1) != 0 || (maxLength & 1)!=0)
    {
        return 0xC000000D; // STATUS_INVALID_PARAMETER
    }

    if ( length > maxLength){
        return 0XC000000D;
    }

    if ( maxLength > 0XFFFE){
        return 0XC000000D;
    }

    if (SourceString -> Buffer == NULL){
        if(length != 0 || maxLength != 0)
        { return 0XC000000D;}
    }

    return 0X00000000; // STATUS_SUCCESS