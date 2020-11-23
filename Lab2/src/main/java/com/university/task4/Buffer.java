package com.university.task4;

import java.util.Arrays;

public class Buffer {

    private final Integer[] buffer;
    private final int maxSize;
    private int currentSize = 0;
    private int nextPos = 0;
    private int startPos = 0;
    private boolean itemLoss;

    public Buffer(int size, boolean itemLoss) {
        this.itemLoss = itemLoss;
        this.maxSize = size;
        this.buffer = new Integer[size];
    }

    public void add(int item) {
        if (currentSize >= maxSize)
            throw new IndexOutOfBoundsException("Adding to full buffer!");

        buffer[nextPos] = item;
        if (itemLoss) {
            try {
                Thread.sleep(1);
                ++currentSize;
            } catch (InterruptedException ex) {
                System.out.println(ex.getMessage());
            }
        } else {
            ++currentSize;
        }
        nextPos = (nextPos + 1) % maxSize;
    }

    public int remove() {
        if (currentSize == 0)
            throw new IndexOutOfBoundsException("Remove from empty buffer!");

        int element = buffer[startPos];
        if (itemLoss) {
            try {
                int newSize = currentSize - 1;
                Thread.sleep(1);
                currentSize = newSize;
            } catch (InterruptedException ex) {
                System.out.println(ex.getMessage());
            }
        } else {
            --currentSize;
        }
        startPos = (startPos + 1) % maxSize;

        return element;
    }

    public int size() {
        return currentSize;
    }

    public void print() {
        System.out.println(Arrays.toString(buffer));
    }
}