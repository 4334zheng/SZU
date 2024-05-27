package Q2;

public class Context {
    private Strategy strategy;
    public Context(Strategy strategy){
        this.strategy = strategy;
    }
    public void lookAlgorithm(){
        strategy.algorithm();
    }
}
