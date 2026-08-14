### Exercise 5 : Decompile the given kernel routines

For the first routine "KeInitializeDpc" , assembly looks like this on my machine (Win11 64-bit):

```assembly
; void __stdcall KeInitializeDpc(PRKDPC Dpc, PKDEFERRED_ROUTINE DeferredRoutine, PVOID DeferredContext)
 public KeInitializeDpc
 KeInitializeDpc proc near               
                                        
                xor     eax, eax
                mov     dword ptr [rcx], 113h
                mov     [rcx+38h], rax
                mov     [rcx+10h], rax
                mov     [rcx+18h], rdx
                mov     [rcx+20h], r8
                retn
KeInitializeDpc endp

When I analyzed _KDPC structure to see what these offsets (0x0 , 0x1 , 0x2 , 0x10 , 0x18 , 0x20 , 0x38) I learnt that they refer to (Type , Importance , Number , ProcessorHistory , DeferredRoutine , DeferredContext and DpcData) , respectively.