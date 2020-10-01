#include "windows.h"
#include <iostream>
#include <tchar.h>
#include "Functions.h"
#include <string>
#include <cstdlib>

#define GET_RESULT 1

using namespace std;

typedef struct{
    int xResult;
    char func;
} RESULT;

COPYDATASTRUCT resultCDS;
RESULT funcResult;
HRESULT hResult;

int  _tmain(int argc, TCHAR *argv[]){

    for(int i = 0; i < argc; i++){
        cout << argv[i] << " - - - STRING NUMBER:" << i << endl;
    }

    if(argc <= 1)
        return -1;

    string argvStrZero = argv[0];
    string argvStrOne = argv[1];
    int xValue;
    bool isInitialized = false;

    if(argvStrZero == "g"){
        xValue = Functions::gFunc(stoi(argvStrOne));
        cout << "THE VALUE OF FUNCTION G:" << xValue << endl;

        isInitialized = true;

    }

    if(argvStrZero == "f"){
        xValue = Functions::fFunc(stoi(argvStrOne));
        cout << "THE VALUE OF FUNCTION F:" << xValue << endl;

        isInitialized = true;
    }

    if(argvStrZero == "b"){
        if(argc < 3)
            return -1;
        int fx, gx;
        string argvStrTwo = argv[2];
        fx = stoi(argvStrOne);
        gx = stoi(argvStrTwo);
        xValue = Functions::binaryOperation(fx, gx);
        cout << "THE VALUE OF FUNCTION B:" << xValue << endl;

        isInitialized = true;
    }

    if(!isInitialized){
        cout << "ERROR" << endl;
        return -1;
    }

    funcResult.xResult = xValue;
    funcResult.func = argvStrZero[0];

    resultCDS.dwData = GET_RESULT;         // function identifier
    resultCDS.cbData = sizeof(funcResult);     // size of data
    resultCDS.lpData = &funcResult;            // data structure

    HWND hwDispatch = FindWindow("hiddenWindowClass", "hiddenWindow");

    if(hwDispatch != nullptr)
        SendMessage(hwDispatch,
                    WM_COPYDATA,
                    (WPARAM)(HWND) nullptr,
                    (LPARAM)(LPVOID) &resultCDS);
    else
        MessageBox(nullptr, "Can't send WM_COPYDATA", "MyApp", MB_OK);

    return 0;
}
