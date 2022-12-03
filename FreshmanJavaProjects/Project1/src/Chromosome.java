import java.util.ArrayList;
import java.util.Random;

public class Chromosome extends ArrayList<Item> implements Comparable<Chromosome> {

    private static Random RNG;

    public Chromosome() {
        //empty constructor
    }

    //Adds a copy of each of the items passed in to this Chromosome.
    //Uses a random number to decide whether each item's included field is set to T or F
    public Chromosome(ArrayList<Item> items){

        Random randGen = new Random();
        ArrayList<Item> copyCombination = new ArrayList<>();

        for (Item i: items){
            //generate random int 0-9, if greater than 4, item is included
            int randFieldSet = randGen.nextInt(10);
            Item copyItem = new Item(i);
            if (randFieldSet > 4){
                copyItem.setIncluded(true);
                this.add(copyItem);
            } else{
                copyItem.setIncluded(false);
                this.add(copyItem);
            }
        }
    }

    //Creates and returns a new child chromosome by performing the crossover operation
    //on this chromosome and the OTHER chromosome that is passed in
    public Chromosome crossover(Chromosome other){

        Chromosome child = new Chromosome();
        Random randParentChoice = new Random();

        int x = 0;
        boolean choice = false;

        for (Item i: this){
            Item copyParent = new Item(i);
            int parentChoice = randParentChoice.nextInt(10);
            //System.out.println(parentChoice);
            if (parentChoice < 5){
                choice = i.isIncluded();
            } if (parentChoice > 4){
                choice = other.get(x).isIncluded();
            }
            copyParent.setIncluded(choice);
            child.add(copyParent);
            x++;
        }

       return child;
    }

    //performs the mutation operation on this chromosome
    public void mutate(){

        Random randMutationChance = new Random();

        for (Item i: this){
            int mutationChance = randMutationChance.nextInt(10);
            if (mutationChance == 0){
                if (i.isIncluded()){
                    i.setIncluded(false);
                } else{
                    i.setIncluded(true);
                }
            }
        }
    }

    //returns the fitness of this chromosome
    public int getFitness(){

        double weight = 0;
        int fitness = 0;

        //for each included item, add its value to fitness
        for (Item i: this){
            if(i.isIncluded()){
                fitness += i.getValue();
                weight += i.getWeight();
                //if weight is greater than 10, fitness = 0
                if (weight > 10){
                    fitness = 0;
                    break;
                }
            }
        }

        return fitness;
    }

    //returns -1 if this chromosome's fitness is greater than the OTHER's fitness
    //returns +1 if this chromosomes fitness is less than the OTHER's fitness
    //returns 0 if fitness is the same
    public int compareTo(Chromosome other){

        if (this.getFitness() > other.getFitness()) {
            return -1;
        } else if (this.getFitness() < other.getFitness()){
            return 1;
        } else {
            return 0;
        }
    }

    //Displays name, weight, and value of all items in this chromosome whose included value is true,
    //followed by the fitness of this chromosome
    public String toString(){

        String nameString = "";

        for (Item i: this){
            if(i.isIncluded()){
                nameString += i.toString();
            }
        }

        nameString += " " + this.getFitness();
        return nameString;
    }


}
