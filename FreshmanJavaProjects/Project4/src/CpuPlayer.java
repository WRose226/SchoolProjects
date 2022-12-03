import java.util.ArrayList;
import java.util.Stack;

public class CpuPlayer extends Player{

    private final int index;


    CpuPlayer(int index, ArrayList<Card> hand){
        super(hand);
        this.index = index;
    }

    public int pickCard(Stack<Card> discardPile){
        //2. player gets to draw a card - if discard pile empty, force pickup from draw pile

        if (discardPile.size() != 0){
            for (Card c: this.hand){
                if (c.getValue() == discardPile.peek().getValue()){
                    return 2;
                }
            }
        }

        return 1;
    }

    public Card discardCard(){
        //3. player discards a single card from their hand
        Card discardCard = null;
        int count = 0;
        int maxCount = 0;

        for (Card c: this.hand){
            count = 0;
            for (Card d: this.hand){
                if (d.getValue() == c.getValue()){
                    count++;
                }
            }
            if (count > maxCount){
                maxCount = count;
            }
        }

        for (Card c: this.hand){
            count = 0;
            for (Card d: this.hand){
                if (d.getValue() == c.getValue()){
                    count++;
                }
            }
            if (count < maxCount || count == 1){
                discardCard = c;
            }
        }

        this.hand.remove(discardCard);
        return discardCard;
    }

    public String toString(){
        return "cpuPlayer" + this.index;
    }
}
