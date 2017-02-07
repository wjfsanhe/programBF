import java.util.concurrent.ExecutorService;
import java.util.concurrent.Callable;
import java.util.concurrent.Future;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Executors;
import java.util.logging.Logger;
import java.util.logging.Level;
import java.util.logging.FileHandler;
import java.util.logging.Formatter;
import java.util.logging.Handler;
import java.util.logging.ConsoleHandler;
import java.io.IOException;
import java.util.logging.SimpleFormatter;
import java.util.logging.LogRecord;
import java.net.InetAddress;

interface ArchiveSearcher { String search(String target); }
class SearcherTest implements ArchiveSearcher{
public   String search(String target){
/*	while (true){
	}
*/
	String c=new String("searching") ;
	System.out.println(c);
	try{	
	Thread.sleep(1000);
	}catch (InterruptedException e){
	}
        return target+"_ret";
        };
}

class myFormatter extends SimpleFormatter{
	public String format(LogRecord record){
		StringBuffer buf = new StringBuffer(1000);
		buf.append("<"+record.getLevel().toString().charAt(0)+">");
		buf.append("["+record.getMillis()+"]:");
		buf.append(formatMessage(record));
		buf.append("\n");
		return buf.toString();
	}
}
class FutureTest {
static    ExecutorService executor ;
private final static Logger LOGGER = Logger.getLogger(FutureTest.class.getName());
static private FileHandler fileTxt;
static private SimpleFormatter formatterTxt;
static    SearcherTest searcher ;
private   void checking_work(Future future)throws InterruptedException{
	boolean exit=false;
	while (!exit){
	   Thread.sleep(300);
	   System.out.println("checking....");
	   //do some work.
	   if(future.isDone()) exit=true;
	}

}
private   void showSearch(final String target)
       throws InterruptedException {
     Future<String> future
       = executor.submit(new Callable<String>() {
         public String call() {
             return searcher.search(target);
         }});
     //checking_work(future);
     /*
     try {
       System.out.println(future.get()); // use future
     } catch (ExecutionException ex) {  return; }
       System.out.println("show search exit");*/
   }
 private final class Shutdown implements Runnable
    {
        public void run()
        {
            
            LOGGER.log(Level.INFO,"shutdown");
        }
    }
 private static hread getMyThread(){
	return new Thread(new Shutdown(), "Shutdown");
	}
public static  void main(String [] args)throws IOException {
	executor=Executors.newFixedThreadPool(4);
	searcher=new SearcherTest();
	FutureTest test=new FutureTest();
	LOGGER.setLevel(Level.INFO);
/*
	try {
	test.showSearch("list");
	}catch(InterruptedException e){
	}*/
//	for(int i=0;i<10;i++)
//	test.showSearch("list"+i);
	Handler[] handlers=LOGGER.getHandlers();
	if (handlers.length!=0  && handlers[0] instanceof ConsoleHandler) {
		LOGGER.warning("handler0 is console");
	}
	fileTxt=new FileHandler("./log.txt");
//	formatterTxt = new SimpleFormatter();
	formatterTxt = new myFormatter();
    	fileTxt.setFormatter(formatterTxt);

	LOGGER.addHandler(fileTxt);
	final InetAddress addr=InetAddress.getLocalHost();
	LOGGER.log(Level.INFO,addr.toString());
        Runtime.getRuntime().addShutdownHook(getMyThread(), "JmDNS.Shutdown");
Thread.sleep(10000);	
	//LOGGER.log(Level.WARNING,"warn Log");
    	//LOGGER.log(Level.INFO,"Info Log");
    	//LOGGER.log(Level.FINEST,"Really not important");

	//System.out.println("*******************************************************************************main exit");
}	
 }
