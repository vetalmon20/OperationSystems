import com.university.BakeryLock;
import org.junit.Assert;
import org.junit.Test;

import java.util.ArrayList;

public class BakeryTest {

    int counter = 0;
    BakeryLock bakeryLock = new BakeryLock();

    @Test
    public void bakeryLockTest_TWOTHREADSTEST() throws InterruptedException {
        Runnable counterIncrementation100 = () -> {
            for(int i = 0; i < 100; i++){
                System.out.println("Locking thread: " + Thread.currentThread().getId());
                bakeryLock.lock();

                counter++;

                bakeryLock.unlock();
                System.out.println("Unlocking thread: " + Thread.currentThread().getId());
            }
        };

        Runnable counterDecrementation100 = () -> {
            for(int i = 0; i < 100; i++){
                System.out.println("Locking thread: " + Thread.currentThread().getId());
                bakeryLock.lock();

                counter--;

                bakeryLock.unlock();
                System.out.println("Unlocking thread: " + Thread.currentThread().getId());
            }
        };

        Runnable counterIncrementation1000 = () -> {
            for(int i = 0; i < 1000; i++){
                System.out.println("Locking thread: " + Thread.currentThread().getId());
                bakeryLock.lock();

                counter++;

                bakeryLock.unlock();
                System.out.println("Unlocking thread: " + Thread.currentThread().getId());
            }
        };

        Runnable counterDecrementation1000 = () -> {
            for(int i = 0; i < 1000; i++){
                System.out.println("Locking thread: " + Thread.currentThread().getId());
                bakeryLock.lock();

                counter--;

                bakeryLock.unlock();
                System.out.println("Unlocking thread: " + Thread.currentThread().getId());
            }
        };

        Runnable counterIncrementation10000 = () -> {
            for(int i = 0; i < 10000; i++){
                System.out.println("Locking thread: " + Thread.currentThread().getId());
                bakeryLock.lock();

                counter++;

                bakeryLock.unlock();
                System.out.println("Unlocking thread: " + Thread.currentThread().getId());
            }
        };

        Runnable counterDecrementation10000 = () -> {
            for(int i = 0; i < 10000; i++){
                System.out.println("Locking thread: " + Thread.currentThread().getId());
                bakeryLock.lock();

                counter--;

                bakeryLock.unlock();
                System.out.println("Unlocking thread: " + Thread.currentThread().getId());
            }
        };

        Thread thread1 = new Thread(counterIncrementation100);
        Thread thread2 = new Thread(counterDecrementation100);
        Thread thread3 = new Thread(counterIncrementation1000);
        Thread thread4 = new Thread(counterDecrementation1000);
        Thread thread5 = new Thread(counterIncrementation10000);
        Thread thread6 = new Thread(counterDecrementation10000);

        thread1.start();
        thread2.start();

        thread1.join();
        thread2.join();

        Assert.assertEquals(counter, 0);
        counter = 0;

        thread3.start();
        thread4.start();

        thread3.join();
        thread4.join();

        Assert.assertEquals(counter, 0);
        counter = 0;

        thread5.start();
        thread6.start();

        thread5.join();
        thread6.join();

        Assert.assertEquals(counter, 0);
    }

    @Test
    public void bakeryLockTest_NTHREADSTEST() throws  InterruptedException {
        counter = 0;
        Runnable counterIncrementation500 = () -> {
            for(int i = 0; i < 500; i++){
                System.out.println("Locking thread: " + Thread.currentThread().getId());
                bakeryLock.lock();

                counter++;

                bakeryLock.unlock();
                System.out.println("Unlocking thread: " + Thread.currentThread().getId());
            }
        };

        Runnable counterDecrementation500 = () -> {
            for(int i = 0; i < 500; i++){
                System.out.println("Locking thread: " + Thread.currentThread().getId());
                bakeryLock.lock();

                counter--;

                bakeryLock.unlock();
                System.out.println("Unlocking thread: " + Thread.currentThread().getId());
            }
        };

        int threadsNum = 10;
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
