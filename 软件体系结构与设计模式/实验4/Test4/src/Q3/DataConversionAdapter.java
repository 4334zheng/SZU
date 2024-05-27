package Q3;

public class DataConversionAdapter implements DataConversion {
    private DataConversion dataConversion;
    public DataConversionAdapter(DataConversion dataConversion) {
        this.dataConversion = dataConversion;
    }
    // 实现接口方法，调用具体的数据转换实现类
    @Override
    public void dataConversion() {
        dataConversion.dataConversion();
    }
}
