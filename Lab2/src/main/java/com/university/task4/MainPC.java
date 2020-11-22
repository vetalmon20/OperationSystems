package com.university.task4;

import java.util.LinkedList;
import java.util.List;

public class MainPC {
    public static final int BufferMax = 5;
    //public static final List<Integer> buffer = new LinkedList<>();
    public static final Buffer buffer = new Buffer(BufferMax, true);

    public static void main(String[] args) {
        Producer p = new Producer(buffer, false);
        Consumer c = new Consumer(buffer);

        p.setConsumer(c);
        c.setProducer(p);

        Thread pThread = new Thread(p);
        Thread cThread = new Thread(c);

        pThread.start();
        cThread.start();
    }
}
