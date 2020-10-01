#include "Functions.h"

Functions::Functions() = default;

Functions::~Functions() = default;

int Functions::fFunc(int x) {
    if(x == 1) {
        return 0;
    }
    if(x == 2)
        Sleep(50000);

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

int Functions::binaryOperation(int fx, int gx) {
    return fx * gx;
}
