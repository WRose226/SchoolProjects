public class Item {

    private final String name;
    private final double weight;
    private final int value;
    private boolean included;

    //initializes the Item's fields to the values that are passed in
    public Item(String name, double weight, int value){
        this.name = name;
        this.weight = weight;
        this.value = value;
        this.included = false;
    }

    //initializes this item's fields to be the same as the other item's
    public Item(Item other){
        this.name = other.name;
        this.weight = other.weight;
        this.value = other.value;
        this.included = other.included;
    }

    //getter classes
    public double getWeight(){
        return this.weight;
    }

    public int getValue(){
        return this.value;
    }

    public boolean isIncluded(){
        return this.included;
    }

    //setter class
    public void setIncluded(boolean included){
        this.included = included;
    }

    //toString class: Displays the item in the form <name> (<weight> lbs, $<value>)
    public String toString(){

        String itemName = name + " (" + weight + " lbs, $" + value + ") ";
        return itemName;
    }

}
