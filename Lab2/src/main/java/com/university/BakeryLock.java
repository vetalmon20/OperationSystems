package com.university;

import java.util.ArrayList;
import java.util.Date;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.Condition;

public class BakeryLock extends AbstractFixNumLock {

    private int MAX_THREAD_ID = 256;
    private static ArrayList<Long> tickets;
    private static ArrayList<Boolean> choosing;

    public BakeryLock(){
        super(256);
        tickets = new ArrayList<>(MAX_THREAD_ID);
        choosing = new ArrayList<>(MAX_THREAD_ID);
        Utils.fillList(MAX_THREAD_ID, 0L, tickets);
        Utils.fillList(MAX_THREAD_ID, false, choosing);
    }

    public BakeryLock(int threadNumber) {
        super(threadNumber);
        tickets = new ArrayList<>(threadNumber);
        choosing = new ArrayList<>(threadNumber);
        Utils.fillList(threadNumber, 0L, tickets);
        Utils.fillList(threadNumber, false, choosing);
    }

    public int getMAX_THREAD_ID() {
        return MAX_THREAD_ID;
    }

    @Override
    public void lock() {
        int id = (int) getId();
        choosing.set(id, true);

        long max = 0;
        for (int i = 0; i < threadNumber; i++) {
            if (tickets.get(i) > max) {
                max = tickets.get(i);
            }
        }
        tickets.set(id, max + 1);

        choosing.set(id, false);

        for (int i = 0; i < tickets.size(); ++i) {
            if (i != id) {
                while (choosing.get(i));
                while (!tickets.get(i).equals(0L) && (tickets.get(id) > tickets.get(i) ||
                        (tickets.get(id).equals(tickets.get(i)) && id > i)));
            }
        }
        System.out.println("In the critical section: " + tickets.get(id));
    }

    @Override
    public void unlock() {
        tickets.set((int) getId(), 0L);
    }

    @Override
    public void lockInterruptibly() {}

    @Override
    public boolean tryLock() { return false; }

    @Override
    public boolean tryLock(long time, TimeUnit unit) { return false; }

    @Override
    public Condition newCondition() {
        return new Condition() {
            @Override
            public void await() throws InterruptedException {

            }

            @Override
            public void awaitUninterruptibly() {

            }

            @Override
            public long awaitNanos(long nanosTimeout) throws InterruptedException {
                return 0;
            }

            @Override
            public boolean await(long time, TimeUnit unit) throws InterruptedException {
                return false;
            }

            @Override
            public boolean awaitUntil(Date deadline) throws InterruptedException {
                return false;
            }

            @Override
            public void signal() {

            }

            @Override
            public void signalAll() {

            }
        };
    }
}