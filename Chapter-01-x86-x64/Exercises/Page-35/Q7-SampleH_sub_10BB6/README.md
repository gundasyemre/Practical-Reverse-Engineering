### Analysis of sub_10BB6

Based on the author's hint to "have a copy of the PE specification nearby," I used Detect It Easy (DiE) to inspect the PE headers of the sample and mapped the hardcoded assembly offsets to standard Windows PE structures. This allowed me to infer the function prototype and decompile the code.

IMAGE_SECTION_HEADER* __stdcall FindPESection(BYTE* baseAddress, const char* name);

Offset Mappings :
    
   1- [eax+3Ch]: Maps to e_lfanew in the IMAGE_DOS_HEADER. It points to the start of the IMAGE_NT_HEADERS
   2- [esi+6]: esi holds the NT Headers address. The +6 offset skips the 4-byte PE Signature and points directly to NumberOfSections inside the IMAGE_FILE_HEADER
   3- [esi+14h]: Points to SizeOfOptionalHeader in the IMAGE_FILE_HEADER
   4- +18h (24 bytes): This is not a magic number; it is the exact combined size of the IMAGE_NT_SIGNATURE (4 bytes) and IMAGE_FILE_HEADER (20 bytes). The code adds this 18h and the SizeOfOptionalHeader together to skip the headers and land exactly on the first IMAGE_SECTION_HEADER
   5- +28h (40 bytes): This is the exact size of a single IMAGE_SECTION_HEADER structure. The loop adds 28h to the pointer (add edi, 28h) in each iteration to jump to the next section in the table
   6- call dword ptr ds:byte_1684F+155h: A dynamic call to a string comparison function (like strncmp) to check if the current section's name matches the target "name" which is an argument to this function.

