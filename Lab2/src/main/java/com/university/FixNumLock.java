package com.university;

import java.util.concurrent.locks.Lock;

public interface FixNumLock extends Lock {

    long getId();
    boolean register();
    boolean unregister();
    void reset();
}
