void __fastcall KeReadyThread(PKTHREAD Thread)
{
  __int64 v1; // r8
  _KPROCESS *Process; // rdi
  PKTHREAD v3; // rbx
  unsigned __int8 CurrentIrql; // si

  Process = Thread->ApcState.Process;
  v3 = Thread;
  if ( (Process->StackCount.Value & 7) == 0 )
    goto LABEL_2;
  CurrentIrql = KeGetCurrentIrql();
  __writecr8(2u);
  if ( KiIrqlFlags )
  {
    LOBYTE(Thread) = CurrentIrql;
    KiRaiseIrqlProcessIrqlFlags(Thread);
  }
  LOBYTE(v1) = CurrentIrql;
  if ( !(unsigned __int8)KiInSwapSingleProcess(v3, Process, v1) )
LABEL_2:
    KiFastReadyThread(v3);
}