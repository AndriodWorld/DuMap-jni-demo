package com.cheerchip.myapplication;

/**
 * Created by clong on 2017/9/16.
 */

public class Jni {

    static {
        System.loadLibrary("native-lib");
    }
    public native int add(int num1,int num2);


    public native  int[] getIntArray(int size);

    public native String stringFromJNI();

    //int 类型数组传递给C
    public native int[] arrayToC(int [] intArray, int [] outArray);

    public native int[] arrayto(int [] intArray);

    public native String strConcat(String str1,String str2);

    //对数组排序
    public native void sortIntArray(int [] intArray);

    //传递对象
    public native Bean newBean(String msg,int what);

    public native String getString(Bean bean);


}
