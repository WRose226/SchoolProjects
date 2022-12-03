class FinishedShoppingEvent extends Event {


    public FinishedShoppingEvent(Customer customer, double time) {
        super(customer, time);

    }

    public String toString(){
        return this.getCustomer() + "Finished shopping at " + super.getTime();
    }

}
