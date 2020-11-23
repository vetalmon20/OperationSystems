package com.university.locks;

import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicIntegerArray;
import java.util.concurrent.locks.Condition;

public class ImprovedBakeryLock extends AbstractFixNumLock {

    AtomicIntegerArray ticket;      // ticket for threads in line, n - number of threads
    AtomicIntegerArray entering;    // 1 when thread entering in line


    public ImprovedBakeryLock(int threadNumber) {
        super(threadNumber);
        this.ticket = new AtomicIntegerArray(threadNumber);
        this.entering = new AtomicIntegerArray(threadNumber);
    }

    private void lock(int threadId) {
        entering.set(threadId, 1);
        int max = 0;
        for (int i = 0; i < getThreadNumber(); ++i) {
            int current = ticket.get(i);
            if (current > max) {
                max = current;
            }
        }
        ticket.set(threadId, max + 1);
        System.out.println("Thread: " + threadId + "\tTicket: " + (1 + max));
        entering.set(threadId, 0);
        for (int i = 0; i < ticket.length(); ++i) {
            if (i != threadId) {
                while (entering.get(i) == 1) {
                    Thread.yield();     // wait while other thread picks a ticket
                }
                while (ticket.get(i) != 0 && (ticket.get(i) < ticket.get(threadId) ||
                        (ticket.get(i) == ticket.get(threadId) && i < threadId))) {
                    Thread.yield();
                }
            }
        }
    }

    @Override
    public void lock() {
        lock(getId());
    }

    private void unlock(int threadId) {
        ticket.set(threadId, 0);
    }

    @Override
    public void unlock() {
        unlock(getId());
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
    public Condition newCondition() {
        return null;
    }
}
