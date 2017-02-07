package com.example.myapp;

import android.app.Activity;
import android.os.Bundle;
import javax.jmdns.JmDNS;
import javax.jmdns.ServiceEvent;
import javax.jmdns.ServiceInfo;
import javax.jmdns.ServiceListener;
import java.io.IOException;
import android.util.Log;

public class MyActivity extends Activity {
    static final String TAG= "myapp";

    static class SampleListener implements ServiceListener {
        public void serviceAdded(ServiceEvent event) {
           Log.i(TAG,"Service added   : " + event.getName()+"."+event.getType());
        }
        public void serviceRemoved(ServiceEvent event) {
           Log.i(TAG,"Service removed : " + event.getName()+"."+event.getType());
        }
        public void serviceResolved(ServiceEvent event) {
            Log.i(TAG,"Service resolved: " + event.getInfo());
        }
    }
    Object o1=new Object();
    Object o2=new Object();
    private class LockThread extends Thread {
            int flag;
            LockThread(int number) {
                flag=number;
            }
            public void run() {
                ServiceInfo  info;
            try{
                JmDNS jmdns = JmDNS.create();
                Log.i(TAG,"start jmdns Listener");
                jmdns.addServiceListener("_airplay._tcp.local.", new SampleListener());
            } catch (IOException e) {
                e.printStackTrace();
            }
            while(true){
                try {
                    Thread.sleep(1000);
                }catch (Exception e){

                }
            }
            /*if(flag==0){
                    synchronized(o1) {
                        try {
                            Thread.sleep(500);
                        }catch (Exception e) {
                            e.printStackTrace();
                        }
                        synchronized(o2) {
                            System.out.println("1");
                        }
                    }
                }else{
                    synchronized(o2) {
                        try {
                            Thread.sleep(500);
                        }catch (Exception e) {
                            e.printStackTrace();
                        }
                        synchronized(o1) {
                            System.out.println("2");
                        }
                    }
                }*/
            }
        }
    /**
     * Called when the activity is first created.
     */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        LockThread TA=new LockThread(0);
        //LockThread TB=new LockThread(1);
        TA.start();
        //TB.start();

        setContentView(R.layout.main);
    }
}
