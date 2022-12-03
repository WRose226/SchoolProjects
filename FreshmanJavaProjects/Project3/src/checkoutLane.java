import java.util.LinkedList;
import java.util.PriorityQueue;

abstract class checkoutLane extends LinkedList<Customer> implements Comparable<checkoutLane> {


    public static PriorityQueue<regularLane> regLanes(int numReg){
        PriorityQueue<regularLane> laneConfiguration = new PriorityQueue<>();
        for (int i=0; i<numReg; i++){
            laneConfiguration.add(new regularLane());
        }
        return laneConfiguration;
    }

    public static PriorityQueue<expressLane> expLanes(int numExpress){
        PriorityQueue<expressLane> laneConfiguration = new PriorityQueue<>();
        for (int i=0; i<numExpress; i++){
            laneConfiguration.add(new expressLane());
        }
        return laneConfiguration;
    }

    public double getCheckoutTime(Customer customer){
        return 0;
    }

    public int compareTo(checkoutLane cl){
        if(this.size() > cl.size()){
            return 1;
        } if (this.size() < cl.size()){
            return -1;
        } else {
            return 0;
        }
    }


}
