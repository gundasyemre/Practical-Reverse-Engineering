char* FindCharReverse(const char *source , char target)
{
    const char* ptr = source + strlen(source);

    while (ptr>=source)
    {

        if ( *ptr == target)
        {
            return (char*)ptr;
        }

        ptr--;
    }
    
    return NULL;
}