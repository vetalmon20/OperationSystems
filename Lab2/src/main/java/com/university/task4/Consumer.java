package com.university.task4;

import java.util.List;

public class Consumer implements Runnable {
    private final Buffer buffer;
    private Producer producer;
    private int lastItem = -1;

    Consumer(Buffer buffer) {
        this.buffer = buffer;
    }

    void setProducer(Producer producer) {
        this.producer = producer;
    }

    @Override
    public void run() {
        while (true) {
            while (buffer.size() == 0) {
                try {
                    synchronized (this) {
                        System.out.println("Consumer: wait");
                        wait();
                        System.out.println("Consumer: wake up");
                    }
                } catch (InterruptedException ex) {
                    System.out.println(ex.getMessage());
                }
            }
            int consumedItem = buffer.remove();
            buffer.print();
            System.out.println("Consumed item: " + consumedItem);
            if (consumedItem - 1 != lastItem) {
                throw new RuntimeException("Item loss: " + lastItem + " - " + consumedItem);
            }
            lastItem = consumedItem;

            if (buffer.size() == MainPC.BufferMax - 1) {
                synchronized (producer) {
                    System.out.println("Consumer: notify");
                    producer.notify();
                }
            }
        }
    }
}
