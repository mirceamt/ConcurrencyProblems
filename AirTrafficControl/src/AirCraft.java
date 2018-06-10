import java.util.Date;

import static java.lang.Thread.*;

/**
 * Created by Ghita on 29-May-16.
 */
public class AirCraft extends Thread
{
    private int mId;
    private AirPort.opType mOpType;
    public AirCraft(int id, AirPort.opType op)
    {
        mId = id;
        mOpType = op;
    }

    public void run()
    {
        int time = (int)(50 + Math.random()*20000);
        try
        {
            Thread.sleep(time);
            AirPort airport  = AirPort.getInstance();
            String s = getOpAsString(mOpType);

            System.out.println(getDateAsString() + ": Aircraft " + mId + " requests to " + s);
            airport.open(mOpType);
            System.out.println(getDateAsString() + ": Aircraft " + mId + " started to " + s);
            airport.simulateDelay(mOpType);
            airport.close();
            System.out.println(getDateAsString() + ": Aircraft " + mId + " finished to " + s);
        }
        catch (Exception e)
        {
            System.out.println(e.getMessage());
        }

    }
    private String  getOpAsString(AirPort.opType op)
    {
        if(op == AirPort.opType.LAND)
            return "LAND";
        return "TAKEOFF";
    }
    private String getDateAsString()
    {
        Date d = new Date();
        return d.toString();
    }
}
