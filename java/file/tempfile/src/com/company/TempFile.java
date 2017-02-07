package com.company;

/**
 * Created by wangjf on 14-6-24.
 */
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.security.KeyPair;
import java.security.KeyPairGenerator;
import java.util.Date;


public class TempFile extends File{
    static final Date CurDate = new Date(System.currentTimeMillis());
    static File keyFile= null;
    String prefix,suffix;
    public TempFile(String pre,String suf){
        super(pre,suf);
        prefix=pre;
        suffix=suf;

    }
    public File GetFile()throws IOException{
        if(null==keyFile) {
            keyFile = File.createTempFile(prefix, CurDate+suffix);
        }
        keyFile.deleteOnExit();
        if(!keyFile.exists()){
            System.out.println("file not exist");
            return null;
        }else{
            return keyFile;
        }

    }
}
