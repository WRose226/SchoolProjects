import java.util.*;
import java.io.*;

public class Main {

    private static final PriorityQueue<regularLane> regularLanes = checkoutLane.regLanes(8);
    private static final PriorityQueue<expressLane> expressLanes = checkoutLane.expLanes(4);
    private static final ArrayList<Customer> customers = new ArrayList<>();
    private static final PriorityQueue<Event> events = new PriorityQueue<>();



    public static void fileIn() throws FileNotFoundException{

            File file = new File("arrival.txt");
            Scanner fileIn = new Scanner(file);

        // for each line, create a customer object for that person and add it to the customers list
        // also create an ArrivalEvent object and add it to the pq

        double timeArrived;
        int orderSize;
        double timePerItem;
        int lineNum = 0;

        while (fileIn.hasNext()){

            timeArrived = fileIn.nextDouble();
            orderSize = fileIn.nextInt();
            timePerItem = fileIn.nextDouble();

            customers.add(new Customer(lineNum, orderSize, timePerItem));
            events.add(new ArrivalEvent(customers.get(lineNum), timeArrived));
            customers.get(lineNum).setArrivalTime(timeArrived);

            lineNum++;
        }

    }


    public static void main(String[] args) throws FileNotFoundException{

        // read in the data file
        fileIn();


        double startTime;
        int numItems;
        double timePerItem;
        double newTime;

        while (events.size() != 0){

            Customer tempCustomer = events.peek().getCustomer();
            System.out.println(regularLanes.peek().size());
            //display event to console
            System.out.println(events.peek());
            Event tempEvent = events.poll();

            if (tempEvent instanceof ArrivalEvent){
                startTime = tempEvent.getTime();

                numItems = tempCustomer.getNumItems();
                timePerItem = tempCustomer.getTimePerItem();
                newTime = startTime + (numItems * timePerItem);
                //setEndShoppingTime for customer
                tempCustomer.setEndShoppingTime(newTime);
                events.add(new FinishedShoppingEvent(tempCustomer, newTime));


            } else if (tempEvent instanceof FinishedShoppingEvent){
                numItems = tempEvent.getCustomer().getNumItems();

                checkoutLane tempLane;
                if (numItems > 12){
                    tempLane = regularLanes.peek();
                    regularLanes.peek().offer(tempCustomer);
                    //poll & offer to update PQ
                    regularLanes.poll();
                    regularLanes.offer((regularLane)tempLane);
                } else {
                    if (regularLanes.peek().size() < expressLanes.peek().size()){
                        tempLane = regularLanes.peek();
                        regularLanes.peek().offer(tempCustomer);
                        //poll & offer to update PQ
                        regularLanes.poll();
                        regularLanes.offer((regularLane)tempLane);

                    } else {
                        tempCustomer.setExpress(true);
                        tempLane = expressLanes.peek();
                        expressLanes.peek().offer(tempCustomer);
                        //poll & offer to update PQ
                        expressLanes.poll();
                        expressLanes.offer((expressLane)tempLane);
                    }
                }


                if (tempLane.size()==1){
                    newTime = tempEvent.getTime() + tempLane.getCheckoutTime(tempCustomer);
                    events.offer(new FinishedCheckoutEvent(tempCustomer, newTime, tempLane));
                    //setEndCheckoutTime for customer
                    tempCustomer.setEndCheckoutTime((newTime));//tempEvent.getCustomer
                }


            } else if (tempEvent instanceof FinishedCheckoutEvent){
                checkoutLane tempLane = ((FinishedCheckoutEvent)tempEvent).getLane();
                //setEndCheckoutTime for customer
                tempCustomer.setEndCheckoutTime(tempEvent.getTime());//tempEvent
                tempLane.remove(tempCustomer);
                if (!tempLane.isEmpty()){
                    tempCustomer = tempLane.peek();

                    newTime = events.peek().getTime() + tempLane.getCheckoutTime(tempCustomer);
                    events.offer(new FinishedCheckoutEvent(tempCustomer, newTime, tempLane));


                }

            }

        }


        waitTimes();

    }

    private static void waitTimes() throws FileNotFoundException {
        PrintWriter pw = new PrintWriter("output.log");

        double total = 0;
        double arrivalTime;
        for (Customer c: customers){
            total += c.getWaitTime();

        }
        pw.println("total customers served " + customers.size());
        pw.println("Average Wait time with " + regularLanes.size() + " regular lanes and " + expressLanes.size() + " express lanes is " + (Math.round(total/customers.size() * 100.0) / 100.0));
        pw.println();
        for (Customer c: customers){
            pw.println(c.dataString());

        }

        pw.close();
    }
}
