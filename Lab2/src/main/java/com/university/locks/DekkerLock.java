package com.university.locks;

import java.util.*;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicLong;
import java.util.concurrent.locks.Condition;

public class DekkerLock extends AbstractFixNumLock {

    private final AtomicLong priorityThread;
    private final ConcurrentHashMap<Long, AtomicBoolean> threadsToEnter;
    private final AtomicBoolean turn;


    public DekkerLock(){
        super(2);
        this.priorityThread = new AtomicLong(-1L);
        threadsToEnter = new ConcurrentHashMap<>(2);
        this.turn = new AtomicBoolean(false);
    }

    @Override
    public void lock() {
        if(!registeredThreads.contains(Thread.currentThread().getId())){
            register();
        }

        long id = getId();
        priorityThread.set(id);
        threadsToEnter.put(id, new AtomicBoolean(true));

        while(threadsToEnter.size() > 1){
            if(turn.get() != (priorityThread.get() == id)){
                threadsToEnter.remove(id);
                while(turn.get() != (priorityThread.get() == id)){}
                threadsToEnter.put(id, new AtomicBoolean(true));
            }
        }
    }

    @Override
    public void unlock() {
        turn.set(!turn.get());
        long id = getId();
        threadsToEnter.remove(id);
    }

    @Override
    public void lockInterruptibly() {}

    @Override
    public boolean tryLock() {
        return false;
    }

    @Override
    public boolean tryLock(long time, TimeUnit unit) {
        return false;
    }

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
