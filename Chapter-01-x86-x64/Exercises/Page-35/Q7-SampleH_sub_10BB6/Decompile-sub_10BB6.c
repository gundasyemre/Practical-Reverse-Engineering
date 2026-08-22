IMAGE_SECTION_HEADER* __stdcall FindPESection(BYTE* baseAddress, const char* name)
{
    IMAGE_NT_HEADERS* ntHeaders = (IMAGE_NT_HEADERS*)(baseAddress +((IMAGE_DOS_HEADER*)baseAddress->e_lfanew);

    IMAGE_SECTION_HEADER* sectionHeader = (IMAGE_SECTION_HEADER*)((BYTE*)ntHeaders+ sizeof(IMAGE_NT_SIGNATURE) + sizeof (IMAGE_FILE_HEADER) + ntHeaders->FileHeader.SizeOfOptionalHeader);
        //+0x18 is not a random number
    for ( int i = 0; i<ntHeaders->FileHeader.NumberOfSections ; i++)
    {
        if (strncmp((const char*)sectionHeader->Name , name , 8)== 0)
        {
            return sectionHeader;
        }
        sectionHeader++;
    }
    return NULL;
}

