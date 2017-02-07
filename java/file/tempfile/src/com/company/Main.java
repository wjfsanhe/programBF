package com.company;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.util.concurrent.TimeUnit;

import static java.lang.Thread.*;
import static java.util.concurrent.TimeUnit.*;

public class Main {

    public static void main(String[] args) throws IOException {
        // write your code here
        TempFile tmpfile=new TempFile("wjf",".key");//
        File file=tmpfile.GetFile();
        String outString=new String("Hello ,man");
        try {//if you love it, Then destroy it.
            OutputStream keyOut = new FileOutputStream(file);
            keyOut.write(outString.getBytes());
            sleep(1000);
            SECONDS.sleep(3);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        try {
            SECONDS.sleep(3);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
