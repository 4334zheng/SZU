package Q1;

public class Trouble {
    private int number;//定义trouble的类型，对应过滤器类型
    public Trouble(int number){
        this.number = number;
    }
    public int getNumber(){
        return this.number;
    }
    public String toString(){
        switch (number) {
            case 1:
                return "[Trouble " + number + " CharTrouble]";
            case 2:
                return "[Trouble " + number + " TypeTransformTrouble]";
            case 3:
                return "[Trouble " + number + " TypeCheckTrouble]";
            default:
                return "No such trouble";
        }
    }
}
