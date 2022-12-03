public class regularLane extends checkoutLane{

    private final double timePerItem = .05;
    private final int processTime = 2;

    public regularLane(){ }

    @Override
    public double getCheckoutTime(Customer customer){
        return this.processTime + (timePerItem * customer.getNumItems());

    }

    public String toString(){
        return "RL(" + timePerItem + ", " + processTime + ")";
    }
}
