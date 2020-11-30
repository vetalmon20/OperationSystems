package com.university.locks;

import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;

public class MonitorLock implements Lock {
    private int threadCount = 0;
    private final Object lock = new Object();


    @Override
    public void lock() {
        synchronized (lock) {
            ++threadCount;
            if (threadCount > 1) {
                try {
                    lock.wait();
                } catch (InterruptedException ex) {
                    System.out.println(ex.getMessage());;
                }
            }
        }
    }

    @Override
    public void lockInterruptibly() throws InterruptedException {

    }

    @Override
    public boolean tryLock() {
        return false;
    }

    @Override
    public boolean tryLock(long time, TimeUnit unit) throws InterruptedException {
        return false;
    }

    @Override
    public void unlock() {
        synchronized (lock) {
            --threadCount;
            lock.notify();
        }
    }

    @Override
    public Condition newCondition() {
        return null;
    }
}
