import java.util.ArrayList;
import java.util.List;
import net.sf.json.JSONArray;
import net.sf.json.JSONObject;


public class students{
    //属性name和age
    private String name;
    private int age;
    //各个属性的get和set方法
    public String getName(){
        return name;
    }
    public void setName(String name){
        this.name = name;
    }
    public int getAge() {
        return age;
    }
    public void setAge(int age) {
        this.age = age;
    }
    //将name和age属性连为一个字符串的toString()方法
    public String toString(){
        return this.name+this.age;
    }
}

