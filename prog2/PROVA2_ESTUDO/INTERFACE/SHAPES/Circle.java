public class Circle implements Shape{
    public int rad;
    public Circle(int rad){
        this.rad = rad;
    }
    @Override
    public double getArea(){
        return(Math.PI * (Math.pow(rad,2)));
    }
}