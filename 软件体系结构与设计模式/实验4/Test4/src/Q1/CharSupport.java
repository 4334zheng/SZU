package Q1;

public class CharSupport extends Support{
    private int typeNum = 1;
    public CharSupport(String name) {
        super(name);
    }

    @Override
    protected boolean resolve(Trouble trouble) {
        if(trouble.getNumber() == typeNum){
            return true;
        }else {
            return false;
        }
    }
}
