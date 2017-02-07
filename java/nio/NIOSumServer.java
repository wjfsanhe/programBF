import java.nio.channels.SelectionKey;
import java.nio.channels.spi.SelectorProvider;
import java.nio.channels.Selector;
import java.nio.ByteBuffer;
import java.nio.IntBuffer;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.net.InetSocketAddress;
import java.net.Socket;

import java.io.IOException;
import java.util.Set;
import java.util.Iterator;
import java.io.InputStream;
import java.io.OutputStream;

/**
* SumServer.java
*
*
* Created: Thu Nov 06 11:41:52 2003
*
* @author starchu1981
* @version 1.0
*/
public class NIOSumServer{
private ByteBuffer _buffer=ByteBuffer.allocate(8);
private IntBuffer _intBuffer=_buffer.asIntBuffer();
private SocketChannel _clientChannel=null;
private int Count=0;
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
_serverChannel.configureBlocking(false);
_serverChannel.socket().bind(new InetSocketAddress(10000));
System.out.println("服务器通道已经打开");
}
private void waitForConnection()throws IOException{
Selector acceptSelector = SelectorProvider.provider().openSelector(); 
SelectionKey acceptKey = _serverChannel.register(acceptSelector, 
SelectionKey.OP_ACCEPT);
int keysAdded = 0;

/*select方法在任何上面注册了的操作发生时返回*/
while ((keysAdded = acceptSelector.select(10000)) > 0) {
System.out.println("new connection coming ini:"+Count++);
// 某客户已经准备好可以进行I/O操作了，获取其ready键集合
Set readyKeys = acceptSelector.selectedKeys();
Iterator i = readyKeys.iterator();
// 遍历ready键集合，并处理加法请求
while (i.hasNext()) {
SelectionKey sk = (SelectionKey)i.next();
i.remove();
ServerSocketChannel nextReady = 
(ServerSocketChannel)sk.channel();
// 接受加法请求并处理它
Socket _clientSocket = nextReady.accept().socket();
processRequest(_clientSocket);
_clientSocket.close();
}
}
System.out.println("quit connection listen");
}
private void processRequest(Socket cliSocket)throws IOException{
_buffer.clear();
InputStream inStream=cliSocket.getInputStream();
inStream.read(_buffer.array());
int result=_intBuffer.get(0)+_intBuffer.get(1);
_buffer.flip();
_buffer.clear();
_intBuffer.put(0,result);
OutputStream outStream=cliSocket.getOutputStream();
outStream.write(_buffer.array());
}
public static void main(String [] args){
SubNet sub=new SubNet();
System.out.println(sub.testInterface("Hello"));
new NIOSumServer().start();
}
} // SumServer
