public class ExperimentalRemoteControlCar implements RemoteControlCar{
    public int distance_traveled;
    public void drive(){
        distance_traveled += 20;
    }
    public int getDistanceTravelled(){
        return distance_traveled;
    }
}