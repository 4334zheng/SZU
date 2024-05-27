package Q3;

public class NaiveBayesClassification extends DataClassification {
    // 调用具体的分类算法
    @Override
    public void dataClassification() {
        System.out.println("使用朴素贝叶斯分类算法进行分类");
    }
    // 创建具体的数据读取实现类
    @Override
    public DataRead getDataRead() {
        return new DataReadImpl();
    }
    // 创建具体的数据转换实现类
    @Override
    public DataConversion getDataConversion() {
        return new DataConversionAdapter(new NaiveBayesDataConversionImpl());
    }
    // 创建具体的分类结果显示实现类
    @Override
    public ClassificationResult getResultDisplay() {
        return new ClassificationResultDisplayImpl();
    }
}
