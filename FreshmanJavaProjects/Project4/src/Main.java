import java.util.*;

public class Main {

    private static final Stack<Card> drawPile = Card.createDeck();
    private static final Stack<Card> discardPile = new Stack<>();
    private static final ArrayList<Player> players = new ArrayList<>();

    public static int gameSetup(){

        //shuffle cards
        Collections.shuffle(drawPile);

        //initialize computer players
        Scanner userIn = new Scanner(System.in);

        int numPlayers;
        while (true){

            try {
                System.out.println("How many computer players (0-3)?");
                numPlayers = Integer.parseInt(userIn.nextLine());
            } catch (InputMismatchException | NumberFormatException e){
                System.out.println("Invalid Input");
                continue;
            }

            if (numPlayers <= 3 && numPlayers >= 0){
                break;
            } else {
                System.out.println("Invalid Input!");
            }
        }


        //each player is given 4 cards
        //remaining cards placed in draw pile; discard pile is empty
        for (int i=0; i<numPlayers+1; i++){
            ArrayList<Card> hand = new ArrayList<>();
            for (int j=0; j<4; j++){
                hand.add(drawPile.pop());
            }
            if (i==0){
                players.add(new HumanPlayer(hand)); //humanPlayer
            } else {
                players.add(new CpuPlayer(i, hand)); //cpuPlayers
            }
        }

        //check for winning hand
        checkForWin();

        //randomly choose player to go first
        Random rand = new Random();
        return rand.nextInt(numPlayers+1);

    }

    public static void main(String[] args){

        Scanner userIn = new Scanner(System.in);
        int turn = gameSetup();


        while (true){

            //1. check if both stacks are empty: if draw pile empty, shuffle discard pile and place in draw pile.
            if (drawPile.size() == 0) {
                Collections.shuffle(discardPile);
                while (discardPile.size() != 0) {
                    drawPile.add(discardPile.pop());
                }
                System.out.println("Discard pile shuffled and replaced on draw pile");
            }


            //2. player gets to draw a card - if discard pile empty, force pickup from draw pile
            // 3. player discards a single card from their hand
            if (players.get(turn) instanceof CpuPlayer){

                System.out.println(players.get(turn).toString() + " will draw a new card.");

                //cpu chooses which card to pick up
                int choice = ((CpuPlayer) players.get(turn)).pickCard(discardPile);
                if (choice == 1){
                    players.get(turn).hand.add(drawPile.pop());
                } else {
                    players.get(turn).hand.add(discardPile.pop());
                }

                //cpu chooses which card to discard
                Card discard = ((CpuPlayer) players.get(turn)).discardCard();
                discardPile.add(discard);
                System.out.println("I will discard the " + discard);

            } else {

                //print out your cards to console
                System.out.println("Your cards are: ");
                for (Card c: players.get(0).getHand()){
                    System.out.println("\t" + c);
                }

                //user chooses which card to pick up
                int choice = 0;
                if (discardPile.size() == 0){
                    System.out.println("The discard pile is currently empty -- you must draw a card");
                    choice = 2;
                } else {
                    System.out.println("The top card in the discard pile is the " + discardPile.peek());
                    System.out.print("Do you want to pick up the " + discardPile.peek() + " (1) or draw a card (2)? " );
                    choice = userIn.nextInt();
                }
                switch (choice){
                    case 1:
                        players.get(0).addCard(discardPile.pop());
                        break;
                    case 2:
                        System.out.println("You drew the " + drawPile.peek());
                        players.get(0).addCard(drawPile.pop());
                        break;
                }

                //print out your cards to console
                System.out.println("Now your cards are: ");
                int cardNum = 1;
                for (Card c: players.get(0).getHand()){
                    System.out.println("\t" + cardNum + ". " +c);
                    cardNum++;
                }
                //user chooses which card to discard
                while (true){
                    try {
                        System.out.print("Which one do you want to discard? ");
                        Card temp = players.get(0).getHand().get(userIn.nextInt()-1);
                        players.get(0).getHand().remove(temp);
                        discardPile.add(temp);
                        break;
                    } catch (IndexOutOfBoundsException e){
                        System.out.println("Invalid input, enter an integer 1-5");
                    }
                }

            }



            //4. check if player has winning hand. If so, display "You win!" or "I win!" & terminate program
            checkForWin();

            //5. next player's turn
            turn++;
            if (turn == players.size()) {
                turn = 0;
            }

        }

    }

    public static void checkForWin(){

        //check players for winning hand
        for (Player p: players) {
            if (p instanceof HumanPlayer) {
                if (p.winCheck()) {
                    System.out.println("You win!");
                    System.exit(0);
                }
            }
            else if (p instanceof CpuPlayer){
                if (p.winCheck()){
                    System.out.println("I win!");
                    System.exit(0);
                }
            }
        }
    }

}
