class FinishedCheckoutEvent extends Event {

    private final checkoutLane lane;

    public FinishedCheckoutEvent(Customer customer, double time, checkoutLane lane) {
        super(customer, time);
        this.lane = lane;
    }

    public checkoutLane getLane(){
        return this.lane;
    }

    public String toString(){
        return this.getCustomer() + "Finished checkout at " + super.getTime();
    }
}

