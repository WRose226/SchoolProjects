class Event implements Comparable<Event> {

    private final Customer customer;
    private final double time;

    public Event(Customer customer, double time) {
        this.time = time;
        this.customer = customer;
    }


    @Override
    public int compareTo(Event e){
        if (this.time > e.time){
            return 1;
        } else if(this.time < e.time){
            return -1;
        } else {
            return 0;
        }
    }

    public double getTime(){
        return this.time;
    }


    public Customer getCustomer(){
        return this.customer;
    }


}