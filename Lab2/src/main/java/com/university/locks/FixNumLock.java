package com.university.locks;

import java.util.concurrent.locks.Lock;

public interface FixNumLock extends Lock {

    int getId();
    boolean register();
    boolean unregister();
    boolean register(long id);
    void reset();
}
