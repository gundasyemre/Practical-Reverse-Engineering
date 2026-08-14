void KeInitializeDpc(PRKDPC Dpc, PKDEFERRED_ROUTINE DeferredRoutine, PVOID DeferredContext) 
{
    Dpc->Type = 19; // Type = 0x13h (19 decimal) , for the offset explanations check README.md on this files directory
    Dpc->Importance = 1; // Importance = 0x1 
    Dpc->Number = 0;
    Dpc->ProcessorHistory = 0;
    Dpc->DeferredRoutine = DeferredRoutine; // Due to fastcall calling convention (my machine is win11 64-bit which uses fastcall convention , even if it says __stdcall in assembly )
    Dpc->DeferredContext = DeferredContext;
    Dpc->DpcData = NULL;
}