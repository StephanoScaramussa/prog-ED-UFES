public class Rectangle implements Shape{
    public int l1;
    public int l2;
    public Rectangle(int l1, int l2){
        this.l1 = l1;
        this.l2 = l2;
    }
    @Override
    public double getArea(){
        return(l1*l2);
    }
}