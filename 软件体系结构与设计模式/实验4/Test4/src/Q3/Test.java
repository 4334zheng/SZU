package Q3;

public class Test {
    public static void main(String[] args) {
        // 使用朴素贝叶斯分类算法进行分类
        DataClassification naiveBayesClassification = new NaiveBayesClassification();
        naiveBayesClassification.dataRead();
        naiveBayesClassification.dataFormatConversion();
        naiveBayesClassification.dataClassification();
        naiveBayesClassification.display();
        System.out.println();
        // 使用决策树分类算法进行分类
        DataClassification decisionTreeClassification = new DecisionTreeClassification();
        decisionTreeClassification.dataRead();
        decisionTreeClassification.dataFormatConversion();
        decisionTreeClassification.dataClassification();
        decisionTreeClassification.display();
        System.out.println();
        // 使用K最近邻分类算法进行分类
        DataClassification knnClassification = new KNNClassification();
        knnClassification.dataRead();
        knnClassification.dataFormatConversion();
        knnClassification.dataClassification();
        knnClassification.display();
    }
}
