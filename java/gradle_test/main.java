import java.nio.charset.Charset;
import java.nio.CharBuffer;
import java.nio.ByteBuffer;
import java.util.Formatter;
import java.net.InetAddress;
import java.util.concurrent.ConcurrentSkipListMap;
import java.io.ByteArrayOutputStream;

class HelloWorld{





//char buffer encode ----> byte buffer.
static private byte[] getBytes (char[] chars) {
   Charset cs = Charset.forName ("UTF-8");
   CharBuffer cb = CharBuffer.allocate (chars.length);
   cb.put (chars);
   cb.flip ();
   ByteBuffer bb = cs.encode (cb);
  
   return bb.array();

 }
static private char[] getChars (byte[] bytes) {
      Charset cs = Charset.forName ("UTF-8");
      ByteBuffer bb = ByteBuffer.allocate (bytes.length);
      bb.put (bytes);
      bb.flip ();
      CharBuffer cb = cs.decode (bb);
  
   return cb.array();
}
public enum EnumTest {
    MON, TUE, WED, THU, FRI, SAT, SUN;
}

public static void main(String[]arg)
throws Exception
{
final ConcurrentSkipListMap<Long, String> frameQueue = new ConcurrentSkipListMap<Long, String>();
ByteArrayOutputStream out=new ByteArrayOutputStream(2);
//
MirrorPacket packet ;
packet = new MirrorStreamPacket();
packet.pushBuffer();
packet = new MirrorCodecPacket();
packet.pushBuffer();





long i=10;
int j=10;
int[] k={1,2,3};

  for (EnumTest e : EnumTest.values()) {
            System.out.println(e.getDeclaringClass()+e.name()+e.toString()+e.ordinal());
        }
for(int l:k)
{
  System.out.println(l+"\r\n");	
}
byte[] input=new byte[100];

input[0]='a';
input[1]='a';
input[2]='a';
input[3]='a';
input[4]='b';

out.write(input,0,100);
out.write(input,0,100);
for (j=0;j<8;j++)
System.out.println("--------"+out.toString());
out.reset();
System.out.println("size:"+out.size()+"after reset");

System.out.println("%"+56);
System.out.println("please input text");
System.in.read(input);
//String str=new String(input,"GB2312");
String str=new String(input,"UTF-8");
String[]  strArr=str.split("/");
for (String item:strArr){
System.out.println("str:  "+ item);
}

if(strArr[2].contains(":")&&strArr[2].contains("7001")){
System.out.println("local");
}else{
System.out.println("remote");
}

	

System.out.print("==="+str);
frameQueue.put(i, "aaaa");
frameQueue.put(i+10, "bbbb");
frameQueue.put(i+5, "cccc");
frameQueue.put(i-9, "dddd");
System.out.println(String.format("%f",3.617427666318E9));

while(!frameQueue.isEmpty())
{
	final long index = frameQueue.firstKey();
	System.out.println("index"+index+",String:"+frameQueue.remove(index));
}


String testStr="Hello";
// string to byte



	
System.out.println("String:"+testStr);
byte[] byteArray=getBytes(testStr.toCharArray());
char[] charArray=getChars(byteArray);
for( i=0;i<charArray.length;i++)
{
	//System.out.printf("%c",charArray[i]);
}
Formatter fmt=new Formatter();
fmt.format("%x-%x-%x",byteArray[0],byteArray[1],byteArray[2]);
System.out.println(fmt);
ByteBuffer byteBuffer=ByteBuffer.allocate(4);
InetAddress  addr=InetAddress.getByName("www.baidu.com");
System.out.println("host address:"+addr.toString());
}
}
