using namespace std;
#include <jni.h>
#include <string>
#include "stdlib.h"
#include "time.h"
#include "MyLog.h"

extern "C"
JNIEXPORT jstring JNICALL
Java_com_cheerchip_myapplication_Jni_getString(JNIEnv *env, jobject instance, jobject bean) {

    jclass clazz=env->FindClass("com/cheerchip/myapplication/Bean");
    //通过类的成员变量直接获取值，反射获取
   /* jfieldID fmsg=env->GetFieldID(clazz,"msg","Ljava/lang/String;");
    jfieldID fwhat=env->GetFieldID(clazz,"what","I");
    jstring jmsg= (jstring) env->GetObjectField(bean, fmsg);
    jint jwhat=env->GetIntField(bean,fwhat);*/

    //通过get方法获取
    jmethodID getMsg=env->GetMethodID(clazz,"getMsg","()Ljava/lang/String;");
    jmethodID getWhat=env->GetMethodID(clazz,"getWhat","()I");
    jstring jmsg= (jstring) env->CallObjectMethod(bean, getMsg);
    jint jwhat=env->CallIntMethod(bean,getWhat);

    //将拿到的值拼装到一个String返回回去
    const char* msg=env->GetStringUTFChars(jmsg,NULL);
    char *str=new char[1024];
    sprintf(str,"Msg:%s;What:%d(From c++)",msg,jwhat);
    jstring rs=env->NewStringUTF(str);
    delete []str;
    env->ReleaseStringUTFChars(jmsg,msg);

    return rs;
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_cheerchip_myapplication_Jni_newBean(JNIEnv *env, jobject instance, jstring msg_, jint what) {
    //const char *msg = env->GetStringUTFChars(msg_, 0);//没必要这样写
    jclass clazz=env->FindClass("com/cheerchip/myapplication/Bean");
    if (NULL==clazz){
        LOGE("can't find class");
        return NULL;
    }

    //方法签名最后为V
    jmethodID jmethodID1=env->GetMethodID(clazz,"<init>","(Ljava/lang/String;I)V");
    if (NULL==jmethodID1){
        LOGE("can't find init function");
        return NULL;
    }
    //调用构造函数获取bean
    jobject bean=env->NewObject(clazz,jmethodID1,msg_,what);
   // env->ReleaseStringUTFChars(msg_, msg);  一定要不能这样写，否则会报错
    return bean;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_cheerchip_myapplication_Jni_sortIntArray(JNIEnv *env, jobject instance, jintArray intArray_) {
    //将数组转为java指针
    jint *intArray = env->GetIntArrayElements(intArray_, NULL);

    jsize size=env->GetArrayLength(intArray_);

    //冒泡算法
    for (int i = 0; i <size-1 ; ++i) {
        for (int j = 0; j < size-1-i; ++j) {
            if(intArray[j]<intArray[j+1]){
                int m=intArray[j];
                intArray[j]=intArray[j+1];
                intArray[j+1]=m;
            }
        }
        
    }
    env->ReleaseIntArrayElements(intArray_, intArray, 0);
    return;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_cheerchip_myapplication_Jni_strConcat(JNIEnv *env, jobject instance, jstring str1_, jstring str2_) {
    const char *str1 = env->GetStringUTFChars(str1_, 0);
    const char *str2 = env->GetStringUTFChars(str2_, 0);

    //计算新的字符串
    int size=strlen(str1)+strlen(str2);
    //创建一个新的字符串，长度+1，为了结尾'\0'
    char * n_char=new char[size+1];
    strcpy(n_char,str1);
    strcat(n_char,str2);
    //将生成的字符串转成UTF的jstring
    jstring rs=env->NewStringUTF(n_char);
    //删除分配的内存
    delete [] n_char;
    //传递jstring和生成的char*.是因为char*有可能是jstring的拷贝，如果是拷贝，那么char*就应该被删除。

    env->ReleaseStringUTFChars(str1_, str1);
    env->ReleaseStringUTFChars(str2_, str2);

    return rs;
}

extern "C"
JNIEXPORT jintArray JNICALL
Java_com_cheerchip_myapplication_Jni_arrayto(JNIEnv *env, jobject instance, jintArray intArray_) {
    jint *intArray = env->GetIntArrayElements(intArray_, NULL);
    jint length=env->GetArrayLength(intArray_);
    for (int i = 0; i <length ; ++i) {
        (intArray[i]) +=10;
        LOGI("i=%d",*(intArray+i));

    }
    env->ReleaseIntArrayElements(intArray_, intArray, 0);
    return intArray_;
}

extern "C"
JNIEXPORT jintArray JNICALL
Java_com_cheerchip_myapplication_Jni_arrayToC(JNIEnv *env, jobject instance, jintArray intArray_, jintArray outArray_) {
    jint *intArray = env->GetIntArrayElements(intArray_, NULL);
    jint *outArray = env->GetIntArrayElements(outArray_, NULL);
    jint length=env->GetArrayLength(intArray_);

    for (int i = 0; i <length ; ++i) {
        (intArray[i])+=10;
        (outArray[i]) = intArray[i];
       // LOGI("i=%d",*(arrayPointer+i));
    }

    env->ReleaseIntArrayElements(intArray_, intArray, 0);
    env->ReleaseIntArrayElements(outArray_, outArray, 0);

    return outArray_;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_cheerchip_myapplication_Jni_stringFromJNI(JNIEnv *env, jobject instance) {

    // TODO
    string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
//定义随机数产生宏 表示产生0~x之间的随机数
#define random(x) (rand()%x)
JNIEXPORT jintArray JNICALL
Java_com_cheerchip_myapplication_Jni_getIntArray(JNIEnv *env, jobject instance, jint size) {

    // TODO
    //用时间变量初始化随机数产生器
    srand((int)time(0));
    jint* rs=new jint[size];
    for (int i = 0; i < size; ++i) {
        //调用宏产生0-100的随机数
        rs[i]=random(100);
    }
    jintArray array=env->NewIntArray(size);
    //把产生的随机数赋给数组
    env->SetIntArrayRegion(array,0,size,rs);
    return array;

}

extern "C"
JNIEXPORT jint JNICALL
Java_com_cheerchip_myapplication_Jni_add(JNIEnv *env, jobject instance, jint num1, jint num2) {

    return num1+num2;


}





