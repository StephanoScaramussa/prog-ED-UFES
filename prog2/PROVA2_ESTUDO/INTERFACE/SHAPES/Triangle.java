public class Triangle implements Shape{
    public int base;
    public int alt;
    public Triangle(int base, int alt){
        this.base = base;
        this.alt = alt;
    }
    @Override
    public double getArea(){
        return((base*alt)/2);
    }
}