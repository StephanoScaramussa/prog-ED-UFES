public class Main{
    public static void main(String[] args){
        Vehicle v1 = new Car();
        Vehicle v2 = new Bycicle();
        v1.speedUp();
        v2.speedUp();
        System.out.println(v1.getSpeed());
        System.out.println(v2.getSpeed());
    }
}