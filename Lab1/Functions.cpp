//
// Created by Laptop on 29.09.2020.
//

#include "Functions.h"
#include "windows.h"

Functions::Functions() {

}

int Functions::fFunc(int x) {
    if(x == 1) {
        return 0;
    }
    if(x == 2)
        Sleep(5000);

    Sleep(2200);
    return x * 2;
}

int Functions::gFunc(int x) {
    if(x == -1) {
        return 0;
    }
    if(x == -2)
        Sleep(5000);

    Sleep(2800);
    return x * 2;
}

