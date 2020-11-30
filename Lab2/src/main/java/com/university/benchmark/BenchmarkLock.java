package com.university.benchmark;

import java.util.concurrent.locks.Lock;

public class BenchmarkLock implements Runnable {
    private Lock lock;
    private int steps;
    private static int counter;


    BenchmarkLock(Lock lock, int steps) {
        this.lock = lock;
        this.steps = steps;
    }

    @Override
    public void run() {
        for (int i = 0; i < steps; ++i) {
            lock.lock();
            ++counter;
            lock.unlock();
        }
    }
}
