public class Main{
    public static void main(String[] args){
        ProductionRemoteControlCar prod = new ProductionRemoteControlCar();
        prod.drive();
        TestTrack.race(prod);
        ExperimentalRemoteControlCar exp = new ExperimentalRemoteControlCar();
        exp.drive();
        TestTrack.race(exp);
        TestTrack.race(new ProductionRemoteControlCar());
    }
}