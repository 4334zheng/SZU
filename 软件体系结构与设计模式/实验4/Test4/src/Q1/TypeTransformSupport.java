package Q1;

public class TypeTransformSupport extends Support{
    private int typeNum = 2;
    public TypeTransformSupport(String name) {
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
