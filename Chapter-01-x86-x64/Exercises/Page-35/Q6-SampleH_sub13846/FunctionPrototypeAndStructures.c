typedef struct _Struct1 Struct1;
typedef struct _Struct2 Struct2;
typedef struct _Struct3 Struct3;
typedef struct _Struct4 Struct4;


void* __fastcall sub_13846(Struct1* a1, Struct2* a2)
{
    Struct3* eax = a1->field_0x60;
    Struct4* esi = a2->field_0x8;

    a1->field_0x23--;

    eax = (Struct3*)((char*)eax - 0x24);

    a1->field_0x60 = eax;

    eax->field_0x14 = a2;

    unsigned int idx = eax->field_0x0;

    FetchFunc myFunc = esi->FunctionTable[idx];

    return myFunc(a1, a2);
}
    