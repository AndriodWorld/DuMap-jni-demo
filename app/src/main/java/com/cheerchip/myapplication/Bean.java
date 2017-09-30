package com.cheerchip.myapplication;

/**
 * Created by clong on 2017/9/28.
 */

public class Bean {

    private String msg;
    private int what;

    public Bean(String msg, int what) {
        this.msg = msg;
        this.what = what;
    }


    public String getMsg() {
        return msg;
    }

    public void setMsg(String msg) {
        this.msg = msg;
    }

    public int getWhat() {
        return what;
    }

    public void setWhat(int what) {
        this.what = what;
    }

    @Override
    public String toString() {
        return "Bean{" +
                "msg='" + msg + '\'' +
                ", what=" + what +
                '}';
    }

}
