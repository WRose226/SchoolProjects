import java.math.BigDecimal;
import java.text.DecimalFormat;

class Customer {

    private static final DecimalFormat df = new DecimalFormat("0.00");

    private final int customerID;
    private final int numItems;
    private final double timePerItem;
    private double endShoppingTime;
    private double endCheckoutTime;
    private double arrivalTime;
    private boolean express;


    public Customer(int customerID, int numItems, double timePerItem){
        this.customerID = customerID;
        this.numItems = numItems;
        this.timePerItem = timePerItem;
        this.endShoppingTime = 0.0;
        this.endCheckoutTime = 0.0;
        this.arrivalTime = 0.0;
        this.express = false;
    }

    public void setExpress(boolean set){
        this.express = set;
    }

    public void setEndShoppingTime(double endShoppingTime){
        this.endShoppingTime =  Double.parseDouble(df.format(endShoppingTime));
    }

    public void setEndCheckoutTime(double endCheckoutTime){
        this.endCheckoutTime = Double.parseDouble(df.format(endCheckoutTime));
    }

    public void setArrivalTime(double arrivalTime){
        this.arrivalTime = arrivalTime;
    }


    public double getWaitTime(){
        double time;
        if (express){
            time = 1 + (this.numItems * .1);
        } else {
            time = 2 + (this.numItems * .05);
        }
        return Double.parseDouble(df.format(this.endCheckoutTime - this.endShoppingTime - time));
    }



    public double getTimePerItem(){
        return this.timePerItem;
    }

    public int getNumItems(){
        return this.numItems;
    }

    public String toString(){
        return "Customer " + this.customerID + "(" + this.numItems + ", " + this.timePerItem + ")";
    }

    public String dataString(){
        return "Customer " + this.customerID + " Arrival: " + this.arrivalTime + ", End Shopping: " + this.endShoppingTime + ", Wait Time: " + getWaitTime() + ", End Checkout: " + this.endCheckoutTime;
    }

}

