//
// Created by Laptop on 02.10.2020.
//

#include "Utils.h"

int* Utils::isInteger(char *s) {
    std::string temp(s);
    int* res = new int(0);
    int i = 0;

    if(temp.empty())
        return nullptr;

    int length = temp.size();

    //if number <0
    if (length > 1 && temp[0] == '-'){
        if (temp[1] >= '1' && temp[1] <= '9'){
            *res = (temp[1] - '0') * (-1);

            for (i = 2; i < length; i++){
                if (temp[i] >= '0' && temp[i] <= '9')
                    *res = *res * 10 - (temp[i] - '0');
                else
                    return nullptr;
            }
            return res;
        } else
            return nullptr;
    }

    //if number >=0
    for (i; i < length; i++){
        if (temp[i] >= '0' && temp[i] <= '9')
            *res = *res * 10 + (temp[i] - '0');
        else
            return nullptr;
    }

    return res;
}
