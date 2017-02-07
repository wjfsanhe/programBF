public class ThreadTest{
public static void main(String [] args){
Thread test = new Thread("test");
test.start();
System.out.println("test started");
test.interrupt();
System.out.println("test stopped");
test.start();
System.out.println("test restart");
} 


}
