package Q3;

public abstract class DataClassification {
    // 读取数据
    public void dataRead() {
        // 调用具体的数据读取实现类
        DataRead dataRead = getDataRead();
        dataRead.dataRead();
    }
    // 数据格式转换
    public void dataFormatConversion() {
        // 调用具体的数据转换实现类
        DataConversion dataConversion = getDataConversion();
        dataConversion.dataConversion();
    }
    // 显示分类结果
    public void display() {
        // 调用具体的分类结果显示实现类
        ClassificationResult resultDisplay = getResultDisplay();
        resultDisplay.display();
    }
    // 调用具体的分类算法
    public abstract void dataClassification();
    // 数据读取实现类
    public abstract DataRead getDataRead();
    // 数据转换实现类
    public abstract DataConversion getDataConversion();
    // 显示实现类
    public abstract ClassificationResult getResultDisplay();
}
