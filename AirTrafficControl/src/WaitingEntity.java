import java.util.concurrent.Semaphore;

public class WaitingEntity
{
    public AirPort.opType  opType;
    public Semaphore mSemaphore;
    public WaitingEntity(AirPort.opType op)
    {
        opType = op;
        mSemaphore = new Semaphore(0);
    }
}
