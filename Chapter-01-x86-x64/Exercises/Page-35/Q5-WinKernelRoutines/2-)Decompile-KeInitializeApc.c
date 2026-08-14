void KeInitializeApc(PKAPC Apc, PKTHREAD Thread, KAPC_ENVIRONMENT Environment, PKKERNEL_ROUTINE KernelRoutine, PKRUNDOWN_ROUTINE RundownRoutine, PKNORMAL_ROUTINE NormalRoutine, KPROCESSOR_MODE ApcMode, PVOID NormalContext)
{
    Apc->Type = 18; //12h
    Apc->Size = 88; //58h

    if (Environment == 2)
    {
        Environment = Thread->ApcStateIndex;
    }

    Apc->ApcStateIndex = Environment;
    Apc->NormalRoutine = NormalRoutine;
    Apc->Thread = Thread;
    Apc->RundownRoutine = RundownRoutine;
    Apc->NormalContext = NormalContext;

    if(NormalContext == 0 )
    {
        ApcMode = 0;
        NormalContext = NULL;
    }

    Apc->ApcMode = ApcMode;
    Apc->SystemArgument1 = NormalContext;
    Apc->Inserted = 0;
}