class ArrivalEvent extends Event {


    public ArrivalEvent(Customer customer, double time) {
        super(customer, time);
    }


    public String toString(){
        return this.getCustomer() + "Arrival at " + super.getTime();
    }

}
