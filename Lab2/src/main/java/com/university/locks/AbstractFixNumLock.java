package com.university.locks;

import com.university.utils.Utils;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public abstract class AbstractFixNumLock implements FixNumLock {

    protected int threadNumber;
    private final Object sync = new Object();
    //protected Set<Long> registeredThreads = new HashSet<>();
    protected List<Long> registeredThreads;

    public AbstractFixNumLock(int threadNumber){
        this.threadNumber = threadNumber;
        this.registeredThreads = new ArrayList<>(threadNumber);
    }

    public int getThreadNumber() {
        return this.threadNumber;
    }

    public List<Long> getRegisteredThreads() {
        return registeredThreads;
    }

    @Override
    public int getId(){
        return registeredThreads.indexOf(Thread.currentThread().getId());
    }

    /*@Override
    public long getId(){
        return Thread.currentThread().getId();
    }*/

    @Override
    public boolean register(){
        synchronized (sync) {
            long id = Thread.currentThread().getId();

            if(registeredThreads.contains(id)){
                System.out.println("The thread with the same id is already present[register func]");
                return false;
            }

            if(registeredThreads.size() >= threadNumber){
                System.out.println("The numbers of threads is exceeded[register func]");
                return false;
            }

            registeredThreads.add(id);
            return true;
        }
    }

    public boolean register(long id){
        synchronized (sync) {
            if(registeredThreads.contains(id)){
                System.out.println("The thread with the same id is already present[register func]");
                return false;
            }

            if(registeredThreads.size() >= threadNumber){
                System.out.println("The numbers of threads is exceeded[register func]");
                return false;
            }

            registeredThreads.add(id);
            return true;
        }
    }

    @Override
    public boolean unregister(){
        synchronized (sync) {
            long id = Thread.currentThread().getId();
            if(!registeredThreads.contains(id)){
                System.out.println("There is no thread with such id[unregister]");
                return false;
            }

            registeredThreads.remove(id);
            return true;
        }
    }

    @Override
    public void reset(){
        synchronized (sync) {
            registeredThreads.clear();
        }
    }
}
