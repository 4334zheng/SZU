#include<iostream>
#include "jni_Demo.h"
using namespace std;

//ʵ��sayHello����
JNIEXPORT void JNICALL Java_jni_Demo_sayHello(JNIEnv* env, jobject obj, jint x, jint y) {
	cout << "x:" << x << ";y:" << y << "x+y=" << x + y << endl;
}