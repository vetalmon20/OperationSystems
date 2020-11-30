package com.university.benchmark;

import com.university.locks.*;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.locks.Lock;

public class MainBenchmarkLock {
    private static Lock lock;
    private static List<Thread> threads;
    private static List<Long> benchmarkTime;
    private static int threadNumber = 8;
    private static int steps = 100_000;
    private static int runs = 10;


    public static void main(String[] args) {
        benchmark();
    }

    public static void benchmark() {
        System.out.println("\n\n====================");
        System.out.println("Results for test: " + runs + " runs, " + steps + " steps, " + threadNumber + " threads\n");

        lock = new ImprovedBakeryLock(threadNumber);
        benchmarkRun();
        print("ImprovedBakeryLock");

        lock = new BakeryLock(threadNumber);
        benchmarkRun();
        print("BakeryLock");

        lock = new SpinLock();
        benchmarkRun();
        print("SpinLock");

//        if (threadNumber == 2) {
//            lock = new DekkerLock();
//            benchmarkRun();
//            print("Dekker Lock");
//        }
        System.out.println("====================\n");
    }

    private static void benchmarkRun() {
        benchmarkTime = new ArrayList<>(runs);
        for (int j = 0; j < runs; ++j) {
            if (lock instanceof FixNumLock) {
                ((FixNumLock) lock).reset();
            }
            threads = new ArrayList<>(threadNumber);
            for (int i = 0; i < threadNumber; ++i) {
                Runnable r = new BenchmarkLock(lock, steps);
                threads.add(new Thread(r));
                if (lock instanceof FixNumLock) {
                    ((FixNumLock) lock).register(threads.get(i).getId());
                }
            }
            long startTime = System.nanoTime();
            for (int i = 0; i < threadNumber; ++i) {
                threads.get(i).start();
            }
            for (int i = 0; i < threadNumber; ++i) {
                try {
                    threads.get(i).join();
                } catch (InterruptedException ex) {
                    System.out.println(ex.getMessage());
                }
            }
            long resultTime = (System.nanoTime() - startTime) / 1_000_000;
            benchmarkTime.add(resultTime);

        }
    }

    private static void print(String lockName) {
        long maxTime = 0;
        long totalTime = 0;
        for (int i = 0; i < runs; ++i) {
            long tempTime = benchmarkTime.get(i);
            totalTime += tempTime;
            if (maxTime < tempTime) {
                maxTime = tempTime;
            }
        }
        long averageTime = totalTime / runs;
        System.out.println("Total: " + totalTime + " ms, average: " + averageTime + " ms, max: " + maxTime + " ms - " + lockName);
    }
}