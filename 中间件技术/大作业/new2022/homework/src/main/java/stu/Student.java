package stu;
/**
 * 学生类
 * @author wch
 */
public class Student {
    private String number = "";
    private String name = "";
    private String gender = "";
    private String major = "";

    public Student(){
        number = ""; name = "";
        gender = ""; major = "";
    }

    /**
     * @description 构造函数,添加单个学生的信息
     * @author wch
     * @param number: 学号
     * @param name: 姓名
     * @param gender: 性别
     * @param major: 主修专业
     */
    public Student(String number, String name, String gender, String major){
        this.number = number;
        this.name = name;
        this.gender = gender;
        this.major = major;
    }

    public String getNumber(){return number;}
    public String getName(){return name;}
    public String getGender(){return gender;}
    public String getMajor(){return major;}
    public void setNumber(String number){this.number = number;}
    public void setName(String name){this.name = name;}
    public void setGender(String gender){this.gender = gender;}
    public void setMajor(String major){this.major = major;}

    /**
     * 重载toString方法
     */
    public String toString(){
        return number + " " + name + " " + gender + " " + major;
    }
    
}
