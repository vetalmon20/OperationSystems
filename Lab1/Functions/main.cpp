#include "windows.h"
#include <iostream>
#include <tchar.h>
#include "Functions.h"
#include <string>
#include <cstdlib>

using namespace std;

int _tmain(int argc, TCHAR *argv[]){

    for(int i = 0; i < argc; i++){
        cout << argv[i] << " - - - STRING NUMBER:" << i << endl;
    }

    //Functions functions;

    string argvStrZero = argv[0];
    string argvStrOne = argv[1];
    int xValue;

    if(argvStrZero == "g"){
        xValue = Functions::gFunc(stoi(argvStrOne));
        cout << "THE VALUE OF FUNCTION G:" << xValue << endl;
        return 0;
    }

    if(argvStrZero == "f"){
        xValue = Functions::fFunc(stoi(argvStrOne));
        cout << "THE VALUE OF FUNCTION F:" << xValue << endl;
        return 0;
    }

    cout << "ERROR" << endl;
    return 0;
}
