package com.university.locks;

import com.university.utils.Utils;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Date;
import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.locks.Condition;

public class BakeryLock extends AbstractFixNumLock {

    private final int MAX_THREAD_ID = 256;
    private static CopyOnWriteArrayList<Integer> tickets;
    //private static List<Integer> tickets;
    private static ArrayList<AtomicBoolean> choosing;

    public BakeryLock(){
        super(256);
        ArrayList<Integer> pseudoTickets = new ArrayList<>(MAX_THREAD_ID);
        Utils.fillList(MAX_THREAD_ID, 0, pseudoTickets);
        tickets = new CopyOnWriteArrayList<>(pseudoTickets);
        choosing = new ArrayList<>(MAX_THREAD_ID);
        //Utils.fillList(MAX_THREAD_ID, new AtomicBoolean(false), choosing);
        Utils.fillList(MAX_THREAD_ID, new AtomicBoolean(false), choosing);
        threadNumber = MAX_THREAD_ID;


        /*super(256);
        threadNumber = 256;
        choosing = new ArrayList<>(Collections.nCopies(threadNumber, new AtomicBoolean(false)));
        tickets = new ArrayList<>(Collections.nCopies(threadNumber, 0));*/

    }

    public BakeryLock(int threadNumber) {
        super(threadNumber);
        ArrayList<Integer> pseudoTickets = new ArrayList<>(threadNumber);
        Utils.fillList(threadNumber, 0, pseudoTickets);
        tickets = new CopyOnWriteArrayList<>(pseudoTickets);
        choosing = new ArrayList<>(threadNumber);
        //Utils.fillList(threadNumber, new AtomicBoolean(false), choosing);
        Utils.fillList(threadNumber, new AtomicBoolean(false), choosing);
        this.threadNumber = threadNumber;


        /*super(threadNumber);
        this.threadNumber = threadNumber;
        choosing = new ArrayList<>(Collections.nCopies(threadNumber, new AtomicBoolean(false)));
        tickets = new ArrayList<>(Collections.nCopies(threadNumber, 0));*/
    }

    public int getMAX_THREAD_ID() {
        return MAX_THREAD_ID;
    }

    @Override
    public void lock() {
        //if(!registeredThreads.contains(Thread.currentThread().getId())){
            //register();
        //}
        //int id = (int) getId();
        int id = getId();
        //choosing.get(id).compareAndSet(false, true);
        choosing.set(id, new AtomicBoolean(true));

        //long max = 0;
        int max = 0;
        for (int i = 0; i < threadNumber; i++) {
            if (tickets.get(i) > max) {
                max = tickets.get(i);
            }
        }
        tickets.set(id, max + 1);

        //choosing.get(id).compareAndSet(true, false);
        choosing.set(id, new AtomicBoolean(false));

        for (int i = 0; i < threadNumber; i++) {
            if (i != id) {
                while (choosing.get(i).get()){}
                while ((!tickets.get(i).equals(0)) && ((tickets.get(id) > tickets.get(i)) ||
                        (tickets.get(id).equals(tickets.get(i)) && (id > i)))){}
            }
        }
        System.out.println("In the critical section: " + tickets.get(id) + " " +  " " + Thread.currentThread().getId());
    }

    @Override
    public void unlock() {
        tickets.set(getId(), 0);
    }

    @Override
    public void lockInterruptibly() {}

    @Override
    public boolean tryLock() { return false; }

    @Override
    public boolean tryLock(long time, TimeUnit unit) { return false; }

    @Override
    public Condition newCondition() {
        return null;
    }
}
