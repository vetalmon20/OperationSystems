import com.university.locks.BakeryLock;
import org.junit.Assert;
import org.junit.Test;

import java.util.ArrayList;

public class BakeryTest {

    int counter = 0;
    BakeryLock bakeryLock;

    @Test
    public void bakeryLockTest_TWOTHREADSTEST() throws InterruptedException {
        bakeryLock = new BakeryLock(2);
        bakeryLock.reset();
        Runnable counterIncrementation = () -> {
            bakeryLock.register();
            for(int i = 0; i < 10000; i++){
                System.out.println("Locking thread: " + Thread.currentThread().getId());
                //System.out.println("Locking thread: " + bakeryLock.getId());
                bakeryLock.lock();

                counter++;

                bakeryLock.unlock();
                System.out.println("Unlocking thread: " + Thread.currentThread().getId());
            }
        };

        Runnable counterDecrementation = () -> {
            bakeryLock.register();
            for(int i = 0; i < 10000; i++){
                System.out.println("Locking thread: " + Thread.currentThread().getId());
                //System.out.println("Locking thread: " + bakeryLock.getId());
                bakeryLock.lock();

                counter--;

                bakeryLock.unlock();
                System.out.println("Unlocking thread: " + Thread.currentThread().getId());
            }
        };

        Thread thread5 = new Thread(counterIncrementation);
        Thread thread6 = new Thread(counterDecrementation);

        thread5.start();
        thread6.start();

        thread5.join();
        thread6.join();

        System.out.println(bakeryLock.getRegisteredThreads().toString());

        Assert.assertEquals(counter, 0);


    }

    @Test
    public void bakeryLockTest_NTHREADSTEST() throws  InterruptedException {
        counter = 0;
        Runnable counterIncrementation500 = () -> {
            bakeryLock.register();
            for(int i = 0; i < 500; i++){
                System.out.println("Locking thread: " + Thread.currentThread().getId());
                bakeryLock.lock();

                counter++;

                bakeryLock.unlock();
                System.out.println("Unlocking thread: " + Thread.currentThread().getId());
            }
        };

        Runnable counterDecrementation500 = () -> {
            bakeryLock.register();
            for(int i = 0; i < 500; i++){
                System.out.println("Locking thread: " + Thread.currentThread().getId());
                bakeryLock.lock();

                counter--;

                bakeryLock.unlock();
                System.out.println("Unlocking thread: " + Thread.currentThread().getId());
            }
        };

        int threadsNum = 8;
        ArrayList<Thread> threads = new ArrayList<>(threadsNum);
        for(int i = 0; i < threadsNum / 2; i++){
            Thread temp1 = new Thread(counterIncrementation500);
            Thread temp2 = new Thread(counterDecrementation500);
            threads.add(temp1);
            threads.add(temp2);
            temp1.start();
            temp2.start();
        }

        for(int i = 0; i < threadsNum; i++){
            threads.get(i).join();
        }

        Assert.assertEquals(counter, 0);
    }
}
