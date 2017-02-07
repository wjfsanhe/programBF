import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class Slf4jTest {
        //  Consolidated in accordance with the APIs that open the slf4j  

        Logger logger = LoggerFactory.getLogger(Slf4jTest.class);   
    
    public void testLog(){   
        logger.info("this is a test log");   
    }    
    public static void main(String[] args) {   
        Slf4jTest slf = new Slf4jTest();   
            slf.testLog();   
    }   
}
