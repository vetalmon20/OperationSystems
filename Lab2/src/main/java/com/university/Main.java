package com.university;

import java.util.HashSet;
import java.util.Set;

public class Main {
    public static void main(String[] args) {
        Set<Long> threadsToEnter = new HashSet<>(2);
        System.out.println(threadsToEnter.size());
        threadsToEnter.add(1L);
        threadsToEnter.add(2L);
        threadsToEnter.remove(1L);
        System.out.println(threadsToEnter.size());
    }
}
