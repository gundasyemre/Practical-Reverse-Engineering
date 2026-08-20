### sub_13846 Analysis

First I realized this function uses __fastcall calling convention because it reads values from ecx and edx into registers , and at the end of assembly there is a call with an index + offset (call dword ptr [esi+eax*4+38h]) which returns a function with a2 and a2 passed as arguments (same as sub_13846 arguments).

About structures : I could see these are structures with fields and the main function of SampleH is named "DriverEntry" , so I assume a1 , a2 (named _Struct1 , _Struct2 by me ) are a kind of I/0 Request Package , so _Struct3 and _Struct4 are one of their fields.

To deduce the exact structures (hopefully) I trust the authors and will come back to this question after finishing Chapter3.