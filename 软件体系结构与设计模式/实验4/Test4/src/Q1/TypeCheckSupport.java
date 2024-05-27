package Q1;

public class TypeCheckSupport extends Support{
    private int typeNum = 3;
    public TypeCheckSupport(String name) {
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
