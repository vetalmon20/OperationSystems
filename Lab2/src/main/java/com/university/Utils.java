package com.university;

import java.util.ArrayList;

public class Utils {

    public static <T> void fillList(int size, T value, ArrayList<T> arrayToFill){
        for(int i = 0; i < size; ++i) {
            arrayToFill.add(value);
        }
    }
}
