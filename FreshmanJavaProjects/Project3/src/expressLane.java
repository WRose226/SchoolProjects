public class expressLane extends checkoutLane{

    private final double timePerItem = 0.1;
    private final int processTime = 1;

    public expressLane(){ }

    @Override
    public double getCheckoutTime(Customer customer){
        return this.processTime + (timePerItem * customer.getNumItems());

    }

    public String toString(){
        return "EL(" + timePerItem + ", " + processTime + ")";
    }
}
