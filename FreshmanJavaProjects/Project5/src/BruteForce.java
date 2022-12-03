import java.io.FileNotFoundException;
import java.util.ArrayList;

public class BruteForce {

    public static void main() throws Exception {
        ArrayList<Item> items = GeneticAlgorithm.readData("items.txt");

        getOptimalSet(items);
    }

    public static ArrayList<Item> getOptimalSet(ArrayList<Item> items) throws Exception {

        int highestFitness = 0;
        ArrayList<Item> bestItemList;

        if (items.size() >= 10){
            throw new Exception("InvalidArgumentException");
        }

        ArrayList<Item> copyItems = new ArrayList<>();
        copyItems.addAll(items);
        Chromosome newChrom = new Chromosome(copyItems);


        // what should the base case be?
        // what is the simplest possible set of items you can have, and
        // which items would you then take with you?

        if (newChrom.getFitness() > highestFitness){
            bestItemList = copyItems;
        }

        // the recursive step for this is a bit like practice problem 7, but with
        // items instead of characters

        // first: what if I take all the items with me? what would the fitness be?
        // consider all the items to be the bestSubset you've seen so far, and
        // their fitness to be the bestFitness you've seen so far

        // second: for each item in the input list of items, what if you
        // didn't take it with you? try recursively calling your method on
        // all the items *except* with the ith item left out. what is the
        // fitness of that subset? If it's better than the best one you've
        // seen so far, update the bestSubset and bestFitness variables
        //
        // note: when you're making the sublist, be sure to create a *COPY*
        // of the input list of items and remove the ith item from the copy
        // instead of the original

        // return the bestSubset you found
        return bestItemList;
    }
}
