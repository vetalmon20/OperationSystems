import com.university.locks.ImprovedBakeryLock;
import org.junit.Assert;
import org.junit.Test;

import java.util.ArrayList;

public class ImprovedBakeryTest {

    int counter = 0;
    ImprovedBakeryLock improvedBakeryLock;

    @Test
    public void improvedBakeryLockTest_TWOTHREADSTEST() throws InterruptedException {
        improvedBakeryLock = new ImprovedBakeryLock(2);
        improvedBakeryLock.reset();
        Runnable counterIncrementation = () -> {
            improvedBakeryLock.register();
            for (int i = 0; i < 10000; ++i) {
                //System.out.println("Locking thread: " + Thread.currentThread().getId());
                improvedBakeryLock.lock();

                ++counter;

                improvedBakeryLock.unlock();
                //System.out.println("Unlocking thread: " + Thread.currentThread().getId());
            }
        };

        Runnable counterDecrementation = () -> {
            improvedBakeryLock.register();
            for (int i = 0; i < 10000; ++i) {
                //System.out.println("Locking thread: " + Thread.currentThread().getId());
                improvedBakeryLock.lock();

                --counter;

                improvedBakeryLock.unlock();
                //System.out.println("Unlocking thread: " + Thread.currentThread().getId());
            }
        };

        Thread t1 = new Thread(counterIncrementation);
        Thread t2 = new Thread(counterDecrementation);

        t1.start();
        t2.start();

        t1.join();
        t2.join();

        System.out.println(improvedBakeryLock.getRegisteredThreads().toString());
        Assert.assertEquals(counter, 0);
    }

    @Test
    public void improvedBakeryLockTest_NTHREADSTEST() throws InterruptedException {
        int threadNumber = 2 * 4;
        improvedBakeryLock = new ImprovedBakeryLock(threadNumber);
        improvedBakeryLock.reset();
        counter = 0;
        Runnable counterIncrementation500 = () -> {
            improvedBakeryLock.register();
            for (int i = 0; i < 500; ++i) {
                //System.out.println("Locking thread: " + Thread.currentThread().getId());
                improvedBakeryLock.lock();

                ++counter;

                improvedBakeryLock.unlock();
                //System.out.println("Unlocking thread: " + Thread.currentThread().getId());
            }
        };

        Runnable counterDecrementation500 = () -> {
            improvedBakeryLock.register();
            for (int i = 0; i < 500; ++i) {
                //System.out.println("Locking thread: " + Thread.currentThread().getId());
                improvedBakeryLock.lock();

                --counter;

                improvedBakeryLock.unlock();
                //System.out.println("Unlocking thread: " + Thread.currentThread().getId());
            }
        };

        ArrayList<Thread> threads = new ArrayList<>(threadNumber);
        for (int i = 0; i < threadNumber / 2; ++i) {
            Thread temp1 = new Thread(counterIncrementation500);
            Thread temp2 = new Thread(counterDecrementation500);
            threads.add(temp1);
            threads.add(temp2);
            temp1.start();
            temp2.start();
        }
        for(int i = 0; i < threadNumber; ++i) {
            threads.get(i).join();
        }
        Assert.assertEquals(counter, 0);
    }
}
