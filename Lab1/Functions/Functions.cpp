#include "Functions.h"

Functions::Functions() = default;

Functions::~Functions() = default;

int Functions::fFunc(int x) {

    if(x == 0){
        Sleep(2000);
        return x * 2 + 1;
    }

    if(x == 1){
        Sleep(3500);
        return x * 2 + 1;
    }

    if(x == 2){
        Sleep(1000);
        return 0;
    }

    if(x == 3)
        Sleep(100000);

    if(x == 4){
        Sleep(2500);
        return x * 2 + 1;
    }

    if(x == 5)
        Sleep(100000);

    Sleep (3100);
    return x * 2 + 1;
}

int Functions::gFunc(int x) {

    if(x == 0){
        Sleep(3000);
        return x * 3 + 1;
    }

    if(x == 1){
        Sleep(2000);
        return x * 3 + 1;
    }

    if(x == 2)
        Sleep(100000);

    if(x == 3){
        Sleep(1500);
        return 0;
    }

    if(x == 4)
        Sleep(100000);

    if(x == 5){
        Sleep(1500);
        return x * 3 + 1;
    }

    Sleep (2200);
    return x * 3 + 1;
}

int Functions::binaryOperation(int fx, int gx) {
    return fx * gx;
}
