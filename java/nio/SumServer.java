import java.nio.ByteBuffer;
import java.nio.IntBuffer;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.net.InetSocketAddress;
import java.io.IOException;
/**
* SumServer.java
*
*
* Created: Thu Nov 06 11:41:52 2003
*
* @author starchu1981
* @version 1.0
*/
public class SumServer {
private ByteBuffer _buffer=ByteBuffer.allocate(8);
private IntBuffer _intBuffer=_buffer.asIntBuffer();
private SocketChannel _clientChannel=null;
private ServerSocketChannel _serverChannel=null;
public void start(){
try{
openChannel();
waitForConnection();
}catch(IOException e){
System.err.println(e.toString());
}
}
private void openChannel()throws IOException{
_serverChannel=ServerSocketChannel.open();
_serverChannel.socket().bind(new InetSocketAddress(10000));
System.out.println("服务器通道已经打开");
}
private void waitForConnection()throws IOException{
while(true){
_clientChannel=_serverChannel.accept();
if(_clientChannel!=null){
System.out.println("新的连接加入");
processRequest();
_clientChannel.close();
}
}
}
private void processRequest()throws IOException{
_buffer.clear();
_clientChannel.read(_buffer);
int result=_intBuffer.get(0)+_intBuffer.get(1);
_buffer.flip();
_buffer.clear();
_intBuffer.put(0,result);
_clientChannel.write(_buffer);
}
public static void main(String [] args){
new SumServer().start();
}
} // SumServer
