import java.util.ArrayList;

public abstract class Player extends ArrayList<Card> {

    protected ArrayList<Card> hand;

    Player(ArrayList<Card> hand){
        this.hand = hand;
    }

    public ArrayList<Card> getHand(){
        return this.hand;
    }

    public void addCard(Card newCard){
        hand.add(newCard);
    }

    public boolean winCheck(){
        if (this.hand.get(0).getValue() == this.hand.get(1).getValue() && this.hand.get(0).getValue() == this.hand.get(2).getValue() && this.hand.get(0).getValue() == this.hand.get(3).getValue()){
            return true;
        } else {
            return false;
        }
    }

}
