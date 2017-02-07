import java.nio.ByteBuffer;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Arrays;
public class test{

private static String[]  CallNewStrBuffer(String[] buf)
{
	String[] temp= new String[4];
	temp[1]="aaaa";
	temp[2]="cccc";
	temp[3]="bbbb";
	temp[0]="dddd";
	return temp;
}
public static int TestFuncWithArray() throws IOException {
String[] buffer=null;
buffer=CallNewStrBuffer(buffer);
System.out.println("buffer size"+buffer.length);
for(int i=0;i<buffer.length;i++)
{
	System.out.println("buffer val:"+buffer[i]);

}
String newStr="11111 222222 333333 444444";
buffer=newStr.split(" ");
for(int i=0;i<buffer.length;i++)
{
        System.out.println("buffer val:"+buffer[i]);

}
byte[] arr1 =null;
byte[] arr2=null;
arr1 =new byte[4];
arr1[0]='a';
arr1[1]='b';
arr1[2]='c';
arr1[3]='d';
String  floatStr= new String("1.2 1.3 1.4 1.5");
arr2=floatStr.getBytes();


ByteBuffer byteBuf=ByteBuffer.wrap(arr2);
//arr2=arr1[2];

System.out.println("offset:"+byteBuf.arrayOffset());
System.out.println("val:"+byteBuf.getFloat());
System.out.println("val:"+byteBuf.getFloat());


 FileInputStream in=new FileInputStream(new File("./line.txt"));
        int count=in.available();
        byte[] fileBuffer=new byte[count];
	in.read(fileBuffer,0,count);
        int idx=0;
	int step=20;
	while(idx<count){
		byte[] ttbuf=new byte[30];	
		step=14;	
		while((idx+step)<count && fileBuffer[idx+step]!=' ') step++;
		System.out.println("step end"+step+" count"+fileBuffer.length);
		ttbuf=Arrays.copyOfRange(fileBuffer,idx,idx+step);
	
		floatStr=new String(ttbuf,"UTF-8");
		System.out.println("once"+floatStr);
		buffer=floatStr.split(" ");
			
        	for(int i=0;i<buffer.length;i++)
		{
        		System.out.println("float val:"+buffer[i].trim());

		}
		idx+=step+1;
		System.out.println("idx end"+idx);
	}





/*for(int i=0;i<arr2.length;i++)
{
        System.out.println("arr val:"+ String.format("%c",arr2[i]));

}*/

	return 1;
}
public static void main(String[]arg) throws IOException{

	System.out.println("we will test para pointer");
	TestFuncWithArray();
}

}
