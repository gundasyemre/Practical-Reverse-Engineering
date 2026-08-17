void __stdcall KeInitializeQueue(PRKQUEUE Queue , ULONG Count)
{
    Queue->Header.Type = 4;
    (&Queue->Header.Lock + 1) = 4096;
    Queue->Header.SignalState = 0;
    Queue->Header.WaitListHead.Blink = &Queue->Header.WaitListHead;
    Queue->Header.WaitListHead.Flink = &Queue->Header.WaitListHead;
    Queue->EntryListHead.Blink = &Queue->EntryListHead;
    Queue->EntryListHead.Flink = &Queue->EntryListHead;
    Queue->ThreadListHead.Blink = &Queue->ThreadListHead;
    Queue->ThreadListHead.Flink = &Queue->ThreadListHead;
    Queue->CurrentCount = 0;
    if(!Count)
        Count = KeQueryActiveProcessorCountEx(0XFFFFu);
    Queue->MaximumCount = Count;
}


    
