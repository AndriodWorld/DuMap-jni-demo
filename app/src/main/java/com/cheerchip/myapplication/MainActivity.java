package com.cheerchip.myapplication;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "MainActivity";

    private Jni jni;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        jni=new Jni();


        final  TextView tv = (TextView) findViewById(R.id.tv_test);
        tv.setText(jni.stringFromJNI()+""+num);

        Bean bean=jni.newBean("hello",15);
        Log.e(TAG,"对象:"+bean.toString());
        String content=jni.getString(bean);
        Log.e(TAG,"string:"+content);


        tv.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                Log.e(TAG,jni.add(3,6)+"");
                //jni.add(3,4);
                //tv.setText(jni.add(5,4)+"");
                String result=operation();
                tv.setText(result);

                Log.e(TAG,"字符串："+jni.strConcat("我很好，","你就是个贱人！"));
                operIntArray();

            }
        });

    }

    private void operIntArray() {
        int [] array=new int[]{1,2,3,4,5};
        int [] array1=new int[5];
        //int []  newArray=jni.arrayToC(array,array1);
        int [] newArray=jni.arrayto(array);
        Log.e(TAG,newArray.length+"长度");
        for (int i:
                newArray) {
            Log.e(TAG,i+"");
        }
        jni.sortIntArray(newArray);
        for (int i:
                newArray) {
            Log.e(TAG,i+"");
        }
    }


    public int num = 10;



    private String operation(){
        int [] rs=jni.getIntArray(10);
        final StringBuilder stringBuilder=new StringBuilder();
        stringBuilder.append('[');
        for (int i:
                rs) {
            stringBuilder.append(i);
            stringBuilder.append(',');
        }
        stringBuilder.deleteCharAt(stringBuilder.length()-1);
        stringBuilder.append(']');
        return stringBuilder.toString();
    }

}
