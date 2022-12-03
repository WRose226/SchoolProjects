public class myTimer {

    private int seconds = 20;
    private int milliseconds = 0;


    public void subtract(){

        if (milliseconds == 0){
            seconds--;
            milliseconds = 99;
        }
        milliseconds--;
    }

    public String toString(){
        if(this.seconds != 0 || this.milliseconds != 0){
            return this.seconds + ":" + this.milliseconds;
        } else{
            return null;
        }
    }

}
