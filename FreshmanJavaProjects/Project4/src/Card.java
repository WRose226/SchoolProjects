import java.util.Stack;

public class Card {

    private final int value;
    private final String suit;

    public Card(int value, String suit){
        this.value = value;
        this.suit = suit;
    }

    public int getValue(){
        return this.value;
    }

    public static Stack<Card> createDeck(){
        Stack<Card> createDeck = new Stack<>();
        String tempSuit;
        int tempValue;
        for (int i=0; i<4; i++){
            if(i == 0){
                tempSuit = "Hearts";
            } else if(i == 1){
                tempSuit = "Spades";
            } else if(i == 2){
                tempSuit = "Diamonds";
            } else {
                tempSuit = "Clubs";
            }
                for (int j=1; j<14; j++){
                    tempValue = j;

                   createDeck.push(new Card(tempValue, tempSuit));
                }
        }

        return createDeck;
    }


    public String toString(){
        String temp = "";
        switch(this.value){
            case 1:
                temp = "Ace";
                break;
            case 2:
                temp = "Two";
                break;
            case 3:
                temp = "Three";
                break;
            case 4:
                temp = "Four";
                break;
            case 5:
                temp = "Five";
                break;
            case 6:
                temp = "Six";
                break;
            case 7:
                temp = "Seven";
                break;
            case 8:
                temp = "Eight";
                break;
            case 9:
                temp = "Nine";
                break;
            case 10:
                temp = "Ten";
                break;
            case 11:
                temp = "Jack";
                break;
            case 12:
                temp = "Queen";
                break;
            case 13:
                temp = "king";
                break;
        }

        return temp + " of " + suit;
    }
}
