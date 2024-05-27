package Q1;

public class Test {
    public static void main(String[] args) {
        Support charSupport = new CharSupport("charSupport");
        Support typeTransformSupport = new TypeTransformSupport("typeTransformSupport");
        Support typeCheckSupport = new TypeCheckSupport("typeCheckSupport");

        charSupport.setNext(typeTransformSupport).setNext(typeCheckSupport);

        for(int i = 1; i <= 4; i++){
            charSupport.support(new Trouble(i));
        }
    }
}
