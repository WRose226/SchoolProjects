import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;

public class myButton extends JButton implements ActionListener{

    private boolean status;
    private Color color;
    private ActionListener event;
    private static int buttonsClicked = 0;

    public void createListener(){
        addActionListener(this);
    }

    public static ArrayList<myButton> getButtonArray(){
        ArrayList<myButton> buttonArray = new ArrayList<>(25);
        for(int i=0; i<25; i++){
            buttonArray.add(new myButton());
            buttonArray.get(i).setColor(Color.WHITE);
            buttonArray.get(i).createListener();
            buttonArray.get(i).setStatus(false);
        }
        return buttonArray;
    }

    @Override
    public void actionPerformed(ActionEvent e){
        if(this.status){
            this.setColor(Color.WHITE);
            this.setStatus(false);
            buttonsClicked++;
        }
    }

    public void setStatus(boolean status){
        this.status = status;
    }

    public boolean getStatus(){
        return this.status;
    }

    public int getButtonsClicked(){
        return buttonsClicked;
    }

    public void setColor(Color color){
        this.color = color;
        this.setBackground(color);
    }


}
