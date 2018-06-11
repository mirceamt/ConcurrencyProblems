import java.util.LinkedList;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class AirPort extends Thread
{
    private static final AirPort airportInstance = new AirPort();
    private AirPort(){}
    public static AirPort getInstance()
    {
        return airportInstance;
    }
    enum opType {
        LAND,
        TAKEOFF
    }

    private static Lock internalLock = new ReentrantLock(true);
    private static LinkedList<WaitingEntity> waitingQueue = new LinkedList<>();
    private static boolean aircraftOnRunway = false;
    private static boolean mTerminationSignaled = false;

    private static Condition mCondition = internalLock.newCondition();

    public void open(opType op) throws InterruptedException {
        WaitingEntity waitingEntity = new WaitingEntity(op);

        internalLock.lock();
        waitingQueue.add(waitingEntity);
        internalLock.unlock();

        waitingEntity.mSemaphore.acquire();
    }

    public  void close()
    {
        internalLock.lock();
        mCondition.signal();
        aircraftOnRunway = false;
        internalLock.unlock();
    }

    public void simulateDelay(opType op) throws InterruptedException {
        int time = 0;
        if(op == opType.LAND)
            time = 5000;
        else
            time = 2000;
        Thread.sleep((long)time);
    }

    @Override
    public void run()
    {
        while(true)
        {
            if(mTerminationSignaled)
                break;
            internalLock.lock();
            if(waitingQueue.isEmpty())
            {
                internalLock.unlock();
                try
                {
                    Thread.sleep(1);
                }
                catch (Exception e){}
                continue;
            }
            if(aircraftOnRunway == true)
            {
                try
                {
                    mCondition.await();
                }
                catch (Exception e)
                {
                    System.out.println(e.getMessage());
                }
            }
            WaitingEntity waitingEntity = waitingQueue.removeFirst();
            aircraftOnRunway = true;
            waitingEntity.mSemaphore.release();
            internalLock.unlock();
        }
    }

    public void closeAirport()
    {
        mTerminationSignaled = true;
    }
}