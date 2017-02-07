public class Counter {
 
    public  static int count = 0;
 
    public static int  get(){
	return count;	
    } 
    public  synchronized static void inc() {
 
        count ++;
    }
 
    public static void main(String[] args) {
 
        //同时启动1000个线程，去进行i++计算，看看实际结果
 
        for (int i = 0; i < 1000; i++) {
            new Thread(new Runnable() {
                @Override
                public void run() {
                    Counter.inc();
                }
            }).start();
        }
 
        //这里每次运行的值都有可能不同,可能为1000
	try {
		Thread.sleep(10);
        } catch (InterruptedException e) {
	}
	System.out.println("运行结果:Counter.count=" + Counter.count);
    }
}
