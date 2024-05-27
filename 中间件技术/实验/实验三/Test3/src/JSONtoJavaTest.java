import net.sf.json.JSONArray;
import net.sf.json.JSONObject;
import net.sf.json.processors.JsonVerifier;

import java.util.ArrayList;
import java.util.List;

public class JSONtoJavaTest {
    //定义javaObjToJSONstr()方法，将一个student对象转换为JSON字符串
    public static void javaObjToJSONstr() {
        students s = new students();
        s.setName("方依依");
        s.setAge(19);
        JSONObject jsonobj = JSONObject.fromObject(s);//后台封装数据
        String str = jsonobj.toString();//调用对象的toString方法
        System.out.println("student对象转换为JSON字符串:");
        System.out.println(str);
    }

    //定义javaArrToJSONstr()方法，将一个含3个student对象的java数组转换为JSON字符串
    public static void javaArrToJSONstr(){
        List<students> s = new ArrayList<students>();//规定存放的类型
        students s1=new students();
        s1.setName("郑彦薇");
        s1.setAge(20);
        s.add(s1);//将对象s1放入s数组
        students s2=new students();
        s2.setName("魏晓欢");
        s2.setAge(19);
        s.add(s2);
        students s3=new students();
        s3.setName("王晓丽");
        s3.setAge(20);
        s.add(s3);
        //后台封装数组数据
        JSONArray jsonarr=JSONArray.fromObject(s);
        //调用toString方法将java数组转换为字符串
        String str=jsonarr.toString();
        System.out.println("Java数组转换为JSON字符串:");
        System.out.println(str);
    }

    //定义jsonStrTojavaObj()方法，将JSON字符串转换为student类对象
    public static void jsonStrTojavaObj(){
        String str="{'name':'方依依','age':17}";
        JSONObject jsonObj=JSONObject.fromObject(str);
        students s=(students) JSONObject.toBean(jsonObj,students.class);//将JSONObject对象转换为java对象
        System.out.println("JSON字符串转换为student对象:");
        System.out.println(s);
    }

    //定义jsonStrToJavaArray()方法，将JSON字符串转换为java数组
    public static void jsonStrToJavaArray(){
        String str="[{'name':'何立立', 'age':21}, {'name':'赵多多','age':22}]";
        JSONArray jsonArr=JSONArray.fromObject(str);
        //定义转换类型为List<students>
        List<students> s=(List<students>) JSONArray.toCollection(jsonArr,students.class);
        System.out.println("JSON字符串转换为java数组:");
        System.out.println(s);
    }

    //main()方法
    public static void main(String[] agrs) {
        javaObjToJSONstr();
        javaArrToJSONstr();
        jsonStrTojavaObj();
        jsonStrToJavaArray();
    }
}
