package com.university;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.concurrent.atomic.AtomicBoolean;

public class Main {
    public static void main(String[] args) {

        ArrayList<AtomicBoolean> aa = new ArrayList<>(50);
        Utils.fillList(50, new AtomicBoolean(true), aa);
        //aa.set(30, new AtomicBoolean(true));
        aa.get(30).set(false);
        System.out.println(aa.get(30));
    }
}
