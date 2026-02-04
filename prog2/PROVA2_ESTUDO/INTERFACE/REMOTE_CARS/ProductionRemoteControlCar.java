public class ProductionRemoteControlCar implements RemoteControlCar{
    public int distance_traveled;
    public void drive(){
        distance_traveled += 10;
    };
    public int getDistanceTravelled(){
        return distance_traveled;
    }
}