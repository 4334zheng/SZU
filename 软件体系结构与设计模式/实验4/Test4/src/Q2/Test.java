package Q2;

public class Test {
    public static void main(String[] args) {
        Strategy preStrategy = new PreCopyStrategy();
        Strategy postStrategy = new PostCopyStrategy();
        Strategy CRRTStrategy = new CRRTMotionStrategy();

        Context preContext = new Context(preStrategy);
        Context postContext = new Context(postStrategy);
        Context CRRTContext = new Context(CRRTStrategy);

        preContext.lookAlgorithm();
        postContext.lookAlgorithm();
        CRRTContext.lookAlgorithm();
    }
}
