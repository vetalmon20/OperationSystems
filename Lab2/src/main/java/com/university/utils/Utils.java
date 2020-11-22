package com.university.utils;

import java.util.ArrayList;
import java.util.Set;

public class Utils {

    public static <T> void fillList(int size, T value, ArrayList<T> arrayToFill){
        for(int i = 0; i < size; ++i) {
            arrayToFill.add(value);
        }
    }

    public static int getIndex(Set<? extends Object> set, Object value) {
        int result = 0;
        for (Object entry:set) {
            if (entry.equals(value))
                return result;
            result++;
        }
        return -1;
    }
}
