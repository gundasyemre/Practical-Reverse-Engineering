KSPIN_LOCK_QUEUE KxWaitForLockChainValid ( PKSPIN_LOCK_QUEUE LockQueue){

    unsigned int SpinCounter;

    KSPIN_LOCK_QUEUE NextQueue;

    SpinCounter = 0;
    
    do
    {
        if((++SpinCounter & HvlLongSpinCountMask)==0 && (HvlEnlightenments & 0x40)!= 0 && KvlCheckVpBackingLongSpinWaitHypercall())
        {
            HvlNotifyLongSpinWait(SpinCounter);
        }
        else{
            _mm_pause();
        }
        NextQueue = *LockQueue->Next;
    } while (!*LockQueue->Next);
    
    return NextQueue;
        
}