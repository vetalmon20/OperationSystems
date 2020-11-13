import com.university.DekkerLock;
import org.junit.Assert;
import org.junit.Test;

public class DekkerTest {

    int counter = 0;
    DekkerLock dekkerLock = new DekkerLock();

    @Test
    public void dekkerCounterTest() throws InterruptedException {
        Runnable counterIncrementation100 = () -> {
            for(int i = 0; i < 100; i++){
                System.out.println("Locking thread: " + Thread.currentThread().getId());
                dekkerLock.lock();

                counter++;

                dekkerLock.unlock();
                System.out.println("Unlocking thread: " + Thread.currentThread().getId());
            }
        };

        Runnable counterIncrementation1000 = () -> {
            for(int i = 0; i < 1000; i++){
                System.out.println("Locking thread: " + Thread.currentThread().getId());
                dekkerLock.lock();

                counter++;

                dekkerLock.unlock();
                System.out.println("Unlocking thread: " + Thread.currentThread().getId());
            }
        };

        Runnable counterIncrementation10000 = () -> {
            for(int i = 0; i < 10000; i++){
                System.out.println("Locking thread: " + Thread.currentThread().getId());
                dekkerLock.lock();

                counter++;

                dekkerLock.unlock();
                System.out.println("Unlocking thread: " + Thread.currentThread().getId());
            }
        };



        Thread thread1 = new Thread(counterIncrementation100);
        Thread thread2 = new Thread(counterIncrementation100);
        Thread thread3 = new Thread(counterIncrementation1000);
        Thread thread4 = new Thread(counterIncrementation1000);
        Thread thread5 = new Thread(counterIncrementation10000);
        Thread thread6 = new Thread(counterIncrementation10000);

        thread1.start();
        thread2.start();

        thread1.join();
        thread2.join();

        Assert.assertEquals(counter, 200);
        counter = 0;

        thread3.start();
        thread4.start();

        thread3.join();
        thread4.join();

        Assert.assertEquals(counter, 2000);
        counter = 0;

        thread5.start();
        thread6.start();

        thread5.join();
        thread6.join();

        Assert.assertEquals(counter, 20000);
    }
}
