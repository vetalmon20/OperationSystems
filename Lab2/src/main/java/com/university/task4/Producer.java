package com.university.task4;

import java.util.List;

public class Producer implements Runnable {
    //private final List<Integer> buffer;
    private final Buffer buffer;
    private Consumer consumer;
    private static final Object monitor = new Object();
    private int nextProducedItem = 0;
    private final boolean deadlock;

    Producer(Buffer buffer, boolean deadlock) {
        this.deadlock = deadlock;
        this.buffer = buffer;
    }

    void setConsumer(Consumer consumer) {
        this.consumer = consumer;
    }

    @Override
    public void run() {
        while (true) {
            while (buffer.size() == MainPC.BufferMax) {
                try {
                    if (deadlock) {
                        Thread.sleep(1);
                    }
                    synchronized (this) {
                        System.out.println("Producer: wait");
                        wait();
                        System.out.println("Producer: wake up");
                    }
                } catch (InterruptedException ex) {
                    System.out.println(ex.getMessage());
                }
            }
            int newItem = nextProducedItem;
            nextProducedItem = (nextProducedItem + 1) % 1_000_000;
            buffer.add(newItem);
            System.out.println("Produced item: " + Integer.toString(newItem));

            if (buffer.size() == 1) {
                synchronized (consumer) {
                    System.out.println("Producer: notify");
                    consumer.notify();
                }
            }
        }
    }
}
