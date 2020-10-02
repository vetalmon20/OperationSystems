#include <tchar.h>
#include <iostream>
#include "demofuncs"
#include "thread"
#include <windows.h>
//#include <commctrl.h>
#include <string>
#include <utility>
#include <vector>
#include <conio.h>
#include <dshow.h>


#define EXEFUNCTIONPATH R"(D:\University\3rd Course\OperationSystems\OperationSystems\Lab1\Functions\cmake-build-debug\Functions.exe)"
#define GET_TEXT 1
#define GET_RESULT 1

using namespace std;

typedef struct{
    int xResult;
    char func;
} RESULT;

int fx, gx;
bool fIsFinished = false;
bool gIsFinished = false;

PCOPYDATASTRUCT pMyCDS;

HWND hEdit, hWrongValue, hFx, hGx, binaryResult, button, hError;
vector<PROCESS_INFORMATION> pinfs;

int res = 0;

static string utf16ToUTF8( const wstring &s )
{
    const int size = ::WideCharToMultiByte( CP_UTF8, 0, s.c_str(), -1, nullptr, 0, nullptr, nullptr );

    vector<char> buf( size );
    ::WideCharToMultiByte( CP_UTF8, 0, s.c_str(), -1, &buf[0], size, nullptr, nullptr );

    return string( &buf[0] );
}

//Convert from char[] to int
bool isInteger(char *s){
    string temp(s);
    if(temp.empty())
        return false;
    res = 0;
    int length = temp.size(), i = 0;

    //if number <0
    if (length > 1 && temp[0] == '-'){
        if (temp[1] >= '1' && temp[1] <= '9'){
            res = (temp[1] - '0') * (-1);

            for (i = 2; i<length; i++){
                if (temp[i] >= '0' && temp[i] <= '9')
                    res = res * 10 - (temp[i] - '0');
                else
                    return false;
            }
            return true;
        } else
            return false;
    }

    //if number >=0
    for (i; i<length; i++){
        if (temp[i] >= '0' && temp[i] <= '9')
            res = res * 10 + (temp[i] - '0');
        else
            return false;
    }

    return true;
}

bool evaluateFunc(LPCTSTR exePath, string func, int x){
    string xStr = std::to_string(x);
    string params = std::move(func);
    //params.push_back(func);
    params += " ";
    params += xStr;
    std::vector<char> cstr(params.c_str(), params.c_str() + params.size() + 1);
    CHAR *paramsChar = reinterpret_cast<char*>(cstr.data());

    STARTUPINFO si = {0};
    PROCESS_INFORMATION pi = {nullptr};
    //CREATE_NO_WINDOW
    if(!CreateProcess(exePath,           // No module name (use command line)
                      paramsChar,        // Command line
                      nullptr,           // Process handle not inheritable
                      nullptr,           // Thread handle not inheritable
                      FALSE,             // Set handle inheritance to FALSE
                      0,                 // No creation flags
                      nullptr,           // Use parent's environment block
                      nullptr,           // Use parent's starting directory
                      &si,               // Pointer to STARTUPINFO structure
                      &pi)){             // Pointer to PROCESS_INFORMATION structure
        printf("CreateProcess failed (%d).\n", GetLastError());
        return false;
    }

    pinfs.push_back(pi);

    return true;
}

bool evaluateBinary(LPCTSTR exePath, string func, int fxVal, int gxVal){
    string fxStr = std::to_string(fxVal);
    string gxStr = std::to_string(gxVal);
    string params = std::move(func);
    //params.push_back(func);
    params += " ";
    params += fxStr;
    params += " ";
    params += gxStr;
    std::vector<char> cstr(params.c_str(), params.c_str() + params.size() + 1);
    CHAR *paramsChar = reinterpret_cast<char*>(cstr.data());

    STARTUPINFO si = {0};
    PROCESS_INFORMATION pi = {nullptr};
    //CREATE_NO_WINDOW
    if(!CreateProcess(exePath,           // No module name (use command line)
                      paramsChar,        // Command line
                      nullptr,           // Process handle not inheritable
                      nullptr,           // Thread handle not inheritable
                      FALSE,             // Set handle inheritance to FALSE
                      0,                 // No creation flags
                      nullptr,           // Use parent's environment block
                      nullptr,           // Use parent's starting directory
                      &si,               // Pointer to STARTUPINFO structure
                      &pi)){             // Pointer to PROCESS_INFORMATION structure
        printf("CreateProcess failed (%d).\n", GetLastError());
        return false;
    }

    return true;
}

bool callFunctions(int x){
    if(!evaluateFunc(EXEFUNCTIONPATH, "f", x))
        return false;
    if(!evaluateFunc(EXEFUNCTIONPATH, "g", x))
        return false;

    return true;
}

bool terminateChildProcesses(){
    for(int i = 0 ; i < pinfs.size(); i++){
        if(!TerminateProcess(pinfs[i].hProcess, 0))
            return false;
        if(!CloseHandle(pinfs[i].hProcess))
            return false;
        if(!CloseHandle(pinfs[i].hThread))
            return false;
        pinfs[i].hProcess = pinfs[i].hThread = nullptr;
    }

    pinfs.clear();

    cout << "PROCESS WERE TERMINATED" << endl;

    return true;
}

/*LRESULT CALLBACK EditCallBckProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData){
    if( (uMsg == WM_CHAR) && (wParam == VK_ESCAPE) )
    {
        cout << "PRESSED EDIT FUNC";
        SetWindowText(hError, "Calculation was terminated by pressing esc button");
        EnableWindow(button, true);
        terminateChildProcesses();
        return 0;
    }
    return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}*/

void addControls(HWND hwnd){
    CreateWindowW(L"static", L"Enter the value of x:", WS_VISIBLE | WS_CHILD,  30, 100, 150, 20, hwnd, nullptr, nullptr, nullptr);
    hEdit = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL, 200, 100, 150, 20, hwnd, nullptr, nullptr, nullptr);
    button = CreateWindowW(L"button", L"Execute!", WS_VISIBLE | WS_CHILD, 100, 200, 200, 100, hwnd, (HMENU)GET_TEXT, nullptr, nullptr);
    hWrongValue = CreateWindowW(L"static", L"", WS_VISIBLE | WS_CHILD, 30, 120, 200, 40, hwnd, nullptr, nullptr, nullptr);
    CreateWindowW(L"static", L"f(x) result:", WS_VISIBLE | WS_CHILD,  30, 400, 100, 20, hwnd, nullptr, nullptr, nullptr);
    CreateWindowW(L"static", L"g(x) result:", WS_VISIBLE | WS_CHILD,  160, 400, 100, 20, hwnd, nullptr, nullptr, nullptr);
    hFx = CreateWindowW(L"static", L"", WS_VISIBLE | WS_CHILD,  30, 420, 100, 20, hwnd, nullptr, nullptr, nullptr);
    hGx = CreateWindowW(L"static", L"", WS_VISIBLE | WS_CHILD,  160, 420, 100, 20, hwnd, nullptr, nullptr, nullptr);
    CreateWindowW(L"static", L"RESULT:", WS_VISIBLE | WS_CHILD,  100, 540, 100, 20, hwnd, nullptr, nullptr, nullptr);
    binaryResult = CreateWindowW(L"static", L"", WS_VISIBLE | WS_CHILD,  100, 570, 100, 20, hwnd, nullptr, nullptr, nullptr);
    hError = CreateWindowW(L"static", L"", WS_VISIBLE | WS_CHILD,  120, 600, 300, 20, hwnd, nullptr, nullptr, nullptr);

    /*SetWindowSubclass(hEdit, &EditCallBckProcedure, 0, 0);*/
}

void addFuncResults(int xResult, char func){

    /*string xResultStr = std::to_string(xResult);
    string funcStr;
    funcStr.push_back(func);
    MessageBox(nullptr, xResultStr.c_str(), funcStr.c_str(), MB_DEFAULT_DESKTOP_ONLY);*/

    if(func == 'f'){
        fx = xResult;
        fIsFinished = true;
    }


    if(func == 'g'){
        gx = xResult;
        gIsFinished = true;
    }

}

void resetFuncResults(){
    fIsFinished = false;
    gIsFinished = false;
}

void resetLabels(){

}



LRESULT CALLBACK hiddenWindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){

    switch(msg){
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_CREATE:
            //addControls(hwnd);
            break;
        case WM_COPYDATA:
            pMyCDS = (PCOPYDATASTRUCT) lp;
            switch(pMyCDS->dwData){
                case GET_RESULT:
                    if(fIsFinished && gIsFinished){

                        string xResult = std::to_string(((RESULT *)(pMyCDS->lpData))->xResult);
                        SetWindowText(binaryResult, xResult.c_str());

                        EnableWindow(button, true);

                    } else {
                        addFuncResults(((RESULT *)(pMyCDS->lpData))->xResult, ((RESULT *)(pMyCDS->lpData))->func);

                        if(((RESULT *)(pMyCDS->lpData))->func == 'g'){
                            string xResult = std::to_string(((RESULT *)(pMyCDS->lpData))->xResult);
                            SetWindowText(hGx, xResult.c_str());

                            if(((RESULT *)(pMyCDS->lpData))->xResult == 0){
                                terminateChildProcesses();

                                EnableWindow(button, true);
                                SetWindowText(hFx, "Undefined");
                                SetWindowText(binaryResult, "0");
                            }


                            if(fIsFinished){
                                evaluateBinary(EXEFUNCTIONPATH, "b", fx, gx);
                            }

                        }

                        if(((RESULT *)(pMyCDS->lpData))->func == 'f'){
                            string xResult = std::to_string(((RESULT *)(pMyCDS->lpData))->xResult);
                            SetWindowText(hFx, xResult.c_str());

                            if(gIsFinished){
                                evaluateBinary(EXEFUNCTIONPATH, "b", fx, gx);
                            } else {

                            }
                        }
                    }

                    break;
            }
            break;

        case WM_KEYDOWN:
            if(wp == VK_ESCAPE){
                cout << "PRESSED HIDDEN WINDOW BUTTON";
                /*SetWindowText(hError, "Calculation was terminated by pressing esc button");
                EnableWindow(button, true);
                terminateChildProcesses();*/
            }
            break;
        default:
            return DefWindowProcW(hwnd, msg, wp, lp);
    }
    return 0;
}

LRESULT CALLBACK myWindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){
    switch(msg){
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_CREATE:
            addControls(hwnd);
            break;
        case WM_COMMAND:
            switch(wp){
                case GET_TEXT:
                    char text[100];
                    GetWindowText(hEdit, text, 100);

                    if(!isInteger(text))
                        SetWindowText(hWrongValue, "Wrong value!");
                    else{
                        resetFuncResults();
                        resetLabels();                                                          ////////////////////

                        int x = std::strtol(text, nullptr, 10);
                        callFunctions(x);
                        SetWindowText(hWrongValue, "");
                        SetWindowText(hError, "");
                        EnableWindow(button, false);
                    }
                    break;
            } 
            break;

        case WM_KEYDOWN:
            if(wp == VK_ESCAPE){
                cout << "PRESSED";
                SetWindowText(hError, "Calculation was terminated by pressing esc button");
                EnableWindow(button, true);
                terminateChildProcesses();
            }
                //PostQuitMessage(0);

            break;
        default:
            return DefWindowProcW(hwnd, msg, wp, lp);
    }
    return 0;
}


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
    //MessageBox(nullptr, "HELLO", "TESTNAME", MB_DEFAULT_DESKTOP_ONLY);

    //WNDCLASSW wc = {0};

    WNDCLASSW wc = {0, myWindowProcedure, 0, 0, hInst,
                    nullptr, LoadCursor(nullptr,IDC_ARROW),(HBRUSH) COLOR_WINDOW,
                    nullptr, L"myWindowClass"};



    if (!RegisterClassW(&wc))
        return -1;

    CreateWindowW(L"myWindowClass", L"WindowName", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 1000, nullptr,
                  nullptr, nullptr, nullptr);

    WNDCLASSW hiddenWindow = {0, hiddenWindowProcedure, 0, 0, hInst,
                    nullptr, nullptr,(HBRUSH) COLOR_WINDOW,
                    nullptr, L"hiddenWindowClass"};

    if (!RegisterClassW(&hiddenWindow))
        return -1;

    CreateWindowW(L"hiddenWindowClass", L"hiddenWindow", WS_OVERLAPPEDWINDOW | SW_HIDE, 800, 100, 100, 100, nullptr,
                  nullptr, nullptr, nullptr);

    MSG msg = {nullptr};

    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }



    return 0;
}