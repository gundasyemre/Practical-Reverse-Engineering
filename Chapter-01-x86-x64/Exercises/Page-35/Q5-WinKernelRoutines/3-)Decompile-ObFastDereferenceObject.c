void ObFastDereferenceObject(union _EX_FAST_REF *FastRef , void *Object){

    signed __int64 CurrentValue;  // my disassembler didn't name this , I came up with this name by logical deduction
    signed __int64 NewValue; // same story with CurrentValue
    signed __int64 OldPointerCount; // same story as above
    bool ShouldDelete // same story as above :)
    signed __int64 BugCheckParameter4; // should credit the disassembler for this one


    _m_prefetchw(FastRef);
    CurrentValue = *(_QWORD *)FastRef;
    while ((unsigned __int64)Object ^ CurrentValue) < 0xF)
    {
        NewValue = CurrentValue;
        CurrentValue = _InterlockedCompareExchange64(volatile signed __int64 *)FastRef, CurrentValue +1 , CurrentValue);
        if (NewValue == CurrentValue)
        {
            if (ObpTraceFlags)
                ObpPushStackInfo((_DWORD)Object - 48);
            return;
        }
    }
    if (ObpTraceFlags)
        ObpPushStackInfo(Object - 48);
    OldPointerCount = _InterlockedExchangeAdd64(Object -6 , 0xFFFFFFFFFFFFFFFFuLL);
    ShouldDelete = OldPointerCount <=1;
    BugCheckParameter4 = OldPointerCount - 1;
    if (ShouldDelete)
    {
        if (Object -5)
            KeBugCheckEx(0x18u, ObjectIndexTable[ObHeaderCookie ^ (Object-24) ^ (Object -48)>> 8], Object, 1u,Object-5);
        
        if ( BugCheckParameter4 < 0 )
            KeBugCheckEx(0x18u, 0, Object , 2u, BugCheckParameter4);
        if (KeGetCurrentThread()->SpecialApcDisable || !KeAreInterruptsEnabled() || KeGetCurrentIrql() )
        {
            ObpDereferObjectDeletion(Object - 48);
        }
        else
        {
            if ( ((Object - 22) & 0x40) != 0 && (Object - ObpInfoMaskToOffset[(Object - 22) & 0x7F] - 48) + 24LL)
            {
                ObpHandleRevocationBlockRemoveObject();
            }
            if (ObpTraceFlags)
                ObpDeregisterObject(Object - 48);
            ObpRemoveObjectRoutine(Object - 48 , 0);
        }
    }
}