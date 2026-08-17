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
```

When I analyzed _KDPC structure to see what these offsets mean (0x0 , 0x1 , 0x2 , 0x10 , 0x18 , 0x20 , 0x38) I learnt that they refer to (Type , Importance , Number , ProcessorHistory , DeferredRoutine , DeferredContext and DpcData) , respectively.

### Decompilation of KeInitializeApc

For "KeInitializeApc" the assembly looks like this :

```assembly
; __int64 __fastcall KeInitializeApc(__int64, __int64, int, __int64, __int64, __int64, unsigned __int8, __int64)
public KeInitializeApc
KeInitializeApc proc near

arg_20= qword ptr  28h
arg_28= qword ptr  30h
arg_30= byte ptr  38h
arg_38= qword ptr  40h

mov     r10, [rsp+arg_38]
mov     byte ptr [rcx], 12h
mov     byte ptr [rcx+2], 58h ; 'X'
cmp     r8d, 2
jnz     short loc_140419DFA
movzx   r8d, byte ptr [rdx+24Ah]
loc_140419DFA:
mov     rax, [rsp+arg_20]
mov     [rcx+50h], r8b
xor     r8d, r8d
mov     [rcx+28h], rax
movzx   eax, [rsp+arg_30]
mov     [rcx+8], rdx
mov     rdx, [rsp+arg_28]
test    rdx, rdx
mov     [rcx+20h], r9
mov     [rcx+30h], rdx
cmovz   eax, r8d
cmovz   r10, r8
mov     [rcx+51h], al
mov     [rcx+38h], r10
mov     [rcx+52h], r8b
mov     [rcx+1], r8b
retn
KeInitializeApc endp
```

As we can see , the disassembler I am using (IDA Pro) couldn't name the arguments (I use microsoft server for path symbols) , so I used "https://www.vergiliusproject.com/kernels/x64/windows-11/25h2/_KAPC" , and learnt the offsets :

```c
//0x58 bytes (sizeof)
struct _KAPC
{
    UCHAR Type;                                                             //0x0
    UCHAR AllFlags;                                                         //0x1
    UCHAR Size;                                                             //0x2
    UCHAR SpareByte1;                                                       //0x3
    ULONG SpareLong0;                                                       //0x4
    struct _KTHREAD* Thread;                                                //0x8
    struct _LIST_ENTRY ApcListEntry;                                        //0x10
    VOID* Reserved[3];                                                      //0x20 , so 0x28 and 0x30 are Reserved[1] and Reserved[2]
    VOID* NormalContext;                                                    //0x38
    VOID* SystemArgument1;                                                  //0x40
    VOID* SystemArgument2;                                                  //0x48
    CHAR ApcStateIndex;                                                     //0x50
    CHAR ApcMode;                                                           //0x51
    UCHAR Inserted;                                                         //0x52
}; 
```

I also learnt that in previous versions of Windows "Reserved" was explicitly written so Reserverd[0] is KernelRoutine , Reserved[1] is  RundownRoutine and Reserved[2] is NormalRoutine.

### Decompilation of ObFastDereferenceObject

Learnt so much just to decompile this , but in short,  I learnt that to dereference an object Windows uses a clever mechanism (_InterlockedCompareExchane64) to speed up the process of deleting the object , and if the fast reference counter is full (0XF) kernel falls back to traditional method and uses negative pointer arithmetic to locate "_OBJECT_HEADER".



### Decompilation of KeInitializeQueue

While analyzing this function , I encountered many "Blink" and "Flink" s , so I decided to learn them :

    Windows embeds a clever circular linked list to its objects (called LIST_ENTRY), the reason I think its clever is because instead of using arrays, vectors which are "faster" structures to implement , this approach of LIST_ENTRY is "safer" because the OS doesnt need to check and deal with null pointers all the time (which can cause more BSODs).

And here is how I dereferenced the offsets :

```c
0000000 struct _KQUEUE // sizeof=0x40
00000000 {                                       
00000000                                       
00000000     DISPATCHER_HEADER Header;           
00000000                                        
00000018     LIST_ENTRY EntryListHead;           
00000018                                         
00000028     volatile ULONG CurrentCount;        
0000002C     ULONG MaximumCount;                 
00000030     LIST_ENTRY ThreadListHead;
00000040 };
```

