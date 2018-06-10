import java.util.concurrent.Semaphore;

/**
 * Created by Ghita on 29-May-16.
 */
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
