package Q3;

// 决策树分类算法
public class DecisionTreeClassification extends DataClassification {
    // 实现抽象方法：调用具体的分类算法
    @Override
    public void dataClassification() {
        System.out.println("使用决策树分类算法进行分类");
    }
    // 实现工厂方法：创建具体的数据读取实现类
    @Override
    public DataRead getDataRead() {
        return new DataReadImpl();
    }
    // 实现工厂方法：创建具体的数据转换实现类
    @Override
    public DataConversion getDataConversion() {
        return new DataConversionAdapter(new DecisionTreeDataConversionImpl());
    }
    // 实现工厂方法：创建具体的分类结果显示实现类
    @Override
    public ClassificationResult getResultDisplay() {
        return new ClassificationResultDisplayImpl();
    }
}
