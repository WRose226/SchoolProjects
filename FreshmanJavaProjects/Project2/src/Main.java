import javax.swing.*;
import javax.swing.border.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.*;
import java.lang.Thread;

class Main extends JFrame{

    //set up variables for Main class
    private static String manual;
    private static final ArrayList<myButton> buttonArray = myButton.getButtonArray();
    private static final JTextArea compComm = new JTextArea();
    public boolean play = true;

    public Main(){

        //create root panel
        JPanel root = new JPanel();
        root.setLayout(new BoxLayout(root, BoxLayout.Y_AXIS));
        root.setPreferredSize(new Dimension(540,640));

        //add panel for textArea
        JPanel textPanel = new JPanel();
        textPanel.setPreferredSize(new Dimension(540, 100));
        root.add(textPanel);

        //add text field to labelPanel at top
        compComm.setFont(new Font("Arial", Font.CENTER_BASELINE, 18));
        compComm.setPreferredSize(new Dimension(520, 80));
        compComm.setBorder(new BevelBorder(0, Color.BLACK,  Color.GRAY));
        textPanel.add(compComm);

        //create panel at bottom of root for game interaction
        JPanel gameZone = new JPanel();
        gameZone.setLayout(new GridLayout(5,5));
        gameZone.setPreferredSize(new Dimension(540,540));

        //add buttons from array to Panel
        for(int i=0; i<25; i++){
            gameZone.add(buttonArray.get(i));
            //buttonArray.get(i).addActionListener(new myButton());
        }

        root.add(gameZone);

        this.getContentPane().add(root);
        this.setTitle("Button Reflex");
        this.setSize(800, 400);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.pack();
        this.setVisible(true);
    }


    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                new Main();
            }
        });

        start();
    }

    public static ActionListener temp;
    private static void start(){
        compComm.setText("Click the squares as fast as you can!");
        buttonArray.get(12).setText("Play");
        buttonArray.get(20).setText("");

         temp = new ActionListener(){
            public void actionPerformed(ActionEvent f) {
                timed();
            }
        };
        buttonArray.get(12).addActionListener(temp);


    }

    public static void timed(){
        buttonArray.get(12).removeActionListener(temp);
        buttonArray.get(12).setText("");
        myTimer countDown = new myTimer();
        Random randButton = new Random();

        //new thread to run the timer
        new Thread(){

            String timeLeft = countDown.toString();
            public void run(){

                while (timeLeft != null){
                    try {
                        Thread.sleep(10);
                    } catch (InterruptedException interruptedException) {
                        interruptedException.printStackTrace();
                    }
                    countDown.subtract();
                    timeLeft = countDown.toString();
                    compComm.setText(timeLeft);
                }
            }
        }.start();

        //new thread to run game interaction
        new Thread(){
            public void run(){

                int random = randButton.nextInt(25);
                buttonArray.get(random).setColor(Color.BLUE);
                buttonArray.get(random).setStatus(true);
                while (countDown.toString()!=null){

                    if(!buttonArray.get(random).getStatus()){

                        random = randButton.nextInt(25);
                        buttonArray.get(random).setColor(Color.BLUE);
                        buttonArray.get(random).setStatus(true);
                    }
                }
                int buttonsClicked = buttonArray.get(0).getButtonsClicked();
                compComm.setText("Your score is " + buttonsClicked + "!");
            }
        }.start();

    }


}
