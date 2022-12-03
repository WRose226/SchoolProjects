import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Random;
import java.util.Scanner;

//public static final int POP_SIZE = 100;
//public static final int NUM_EPOCHS = 1000;
//public static final int NUM_THREADS = 1;

public class GeneticAlgorithm {

    //Reads in a data file and returns an ArrayList of objects
    public static ArrayList<Item> readData(String fileName) throws FileNotFoundException{

        //scans items.txt into program using a delimiter
        Scanner fileIn = new Scanner(new File(fileName)).useDelimiter(", |\n");

        ArrayList<Item> items = new ArrayList<>();
        //create arraylist of objects using data from text file
        while (fileIn.hasNext()){
            String name = fileIn.next();
            double weight = fileIn.nextDouble();
            int value = Integer.parseInt(fileIn.next().trim());

            //create item object based on scanned data
            items.add(new Item(name, weight, value));
        }

        return items;
    }

    //Creates and returns an ArrayList of populationSize Chromosome objects that each contain the items,
    //with their included field randomly set to T or F
    public static ArrayList<Chromosome> initializePopulation(ArrayList<Item> items, int populationSize){

        //creates ArrayList of chromosomes, called generation
        ArrayList<Chromosome> generation = new ArrayList<>();

        //passes in items into Chromosome; adds chromosome to arraylist
        for (int i=0; i<populationSize; i++){
            generation.add(new Chromosome(items));
        }
        return generation;
    }

    /*
    Reads the data about the items in from a file called items.txt and performs steps:
    1.	Create a set of ten random individuals to serve as the initial population.
    2.	Add	each of	the	individuals	in the current population to the next generation.
    3.	Randomly pair off the individuals and perform crossover	to create a	child and add it to
        the	next generation	as well.
    4.  Randomly choose ten percent of the individuals in the next generation and expose them to mutation
    5.  Sort the individuals in the next generation according to their fitness.
    6.  Clear out the current population and add the top ten of the next generation back into the population.
    7. Repeat steps 2 - 6 twenty times.
    8. Sort the population and display the fittest individual to the console.
     */
    public static void main(String[] args) throws FileNotFoundException {

        //calls method readData to read in items from text file
        ArrayList<Item> items = readData("more_items.txt");

        //sets populationSize to pass into initializePopulation method
        int populationSize = 100;
        ArrayList<Chromosome> currentPopulation = initializePopulation(items, populationSize);

        //initialize next generation chromosome arraylist
        ArrayList<Chromosome> nextGeneration = new ArrayList<>();
        //loop for n generations(20 in this case)
        for (int i=0; i<500; i++){
            //copy chromosomes from currentPopulation & add to nextGeneration
            for (Chromosome c: currentPopulation){
                Chromosome copyChromosome = c;
                nextGeneration.add(copyChromosome);
                //System.out.println("copy chromosome: " + copyChromosome);
            }

            //generate random number, get chromosomes, pass into crossover method
            Random randCross = new Random();
            int cross1 = randCross.nextInt(nextGeneration.size());
            int cross2 = cross1;
            //ensures cross2 will not equal cross1: to ensure crossover doesn't happen with the same parent
            do{
                cross2 = randCross.nextInt(nextGeneration.size());
            } while (cross2 == cross1);

            //create child chromosome by performing crossover between 2 random chromosomes from nextGeneration ArrayList
            Chromosome childChromosome = nextGeneration.get(cross1).crossover(nextGeneration.get(cross2));
            //System.out.println(nextGeneration.get(cross1));
            //System.out.println(nextGeneration.get(cross2));
            //System.out.println("child chromosome " + childChromosome.toString());

            //add childChromosome to nextGeneration
            nextGeneration.add(childChromosome);


            //changes 10% to an integer of chromosomes to be mutated
            int mutateSize = (int)(nextGeneration.size() * (.1));
            //initialize ArrayList to hold number of Chromosome to be mutated
            ArrayList<Integer> mutateStore = new ArrayList<>();
            int randMutate=0;
            //loop to mutate 10% of the population
            for (int j=0; j<mutateSize; j++){

                //loop to make sure the chromosome to be mutated wasn't already selected for mutation
                do{
                    randMutate = randCross.nextInt(nextGeneration.size());
                } while (mutateStore.contains(randMutate));
                //add number to mutateStore ArrayList
                mutateStore.add(randMutate);

                //mutate the randomly selected Chromosome
                nextGeneration.get(randMutate).mutate();
            }

            //clear mutateStore ArrayList to prepare for the next generation mutation
            mutateStore.clear();

            //sort individuals in nextGeneration according to fitness
            Collections.sort(nextGeneration);

            //clear out currentPopulation, choose top 10 from nextGeneration and add to currentPopulation
            currentPopulation.clear();
            for(int k=0; k<populationSize; k++){
                currentPopulation.add(nextGeneration.get(k));
            }
            nextGeneration.clear();

            Collections.sort(currentPopulation);
            System.out.println(currentPopulation.get(0).getFitness());
        }

        //sort population and display fittest individual to console
        Collections.sort(currentPopulation);
        System.out.println(currentPopulation.get(0));

    }
}
