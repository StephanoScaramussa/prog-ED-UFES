public class Main{
    public static void main(String[] args){
        Rectangle rec1 = new Rectangle(10,20);
        System.out.println(rec1.getArea());
        Circle c1 = new Circle(10);
        System.out.println(c1.getArea());
        Triangle t1 = new Triangle(10,3);
        System.out.println(t1.getArea());
    }
}