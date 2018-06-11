import java.util.Random;

public class AirTrafficControl
{
    public static void main(String[] args) throws InterruptedException
    {
        AirPort airPort = AirPort.getInstance();
        airPort.start();

        int noOfAirCrafts = 10;

        AirCraft[] airCrafts = new AirCraft[noOfAirCrafts];
        Random r = new Random();
        for(int i = 0; i < noOfAirCrafts; ++i)
        {
            int n = r.nextInt()%2;
            if( n == 0)
                airCrafts[i] = new AirCraft(i,AirPort.opType.LAND);
            else
                airCrafts[i] = new AirCraft(i,AirPort.opType.TAKEOFF);
        }
        for (int i = 0; i < noOfAirCrafts; ++i)
            airCrafts[i].start();
        for (int i = 0; i < noOfAirCrafts; ++i)
            airCrafts[i].join();
        airPort.closeAirport();
    }
}