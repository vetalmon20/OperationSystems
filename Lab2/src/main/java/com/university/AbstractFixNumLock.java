package com.university;

import java.util.HashSet;
import java.util.Set;

public abstract class AbstractFixNumLock implements FixNumLock {

    protected static int threadNumber = 10;
    private final Object sync = new Object();
    protected Set<Long> registeredThreads = new HashSet<>();

    public AbstractFixNumLock() {}
    public AbstractFixNumLock(int threadNumber){
        AbstractFixNumLock.threadNumber = threadNumber;
    }

    public static int getThreadNumber() {
        return threadNumber;
    }

    public Set<Long> getRegisteredThreads() {
        return registeredThreads;
    }

    @Override
    public long getId(){
        return Thread.currentThread().getId();
    }

    @Override
    public boolean register(){
        synchronized (sync) {
            long id = Thread.currentThread().getId();

            if(registeredThreads.contains(id)){
                System.out.println("The thread with the same id is already present[register func]");
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
