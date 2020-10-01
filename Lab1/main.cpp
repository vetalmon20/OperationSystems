#include <iostream>
#include "demofuncs"
#include "thread"
#include <windows.h>
#include <string>
#include <vector>
#include <conio.h>

using namespace std;

#define GET_TEXT 1

HWND hEdit, hWrongValue;
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

void addControls(HWND hwnd){
    CreateWindowW(L"static", L"Enter the value of x:", WS_VISIBLE | WS_CHILD,  30, 100, 150, 20, hwnd, nullptr, nullptr, nullptr);
    hEdit = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL, 200, 100, 150, 20, hwnd, nullptr, nullptr, nullptr);
    CreateWindowW(L"button", L"Execute!", WS_VISIBLE | WS_CHILD, 100, 200, 200, 100, hwnd, (HMENU)GET_TEXT, nullptr, nullptr);
    hWrongValue = CreateWindowW(L"static", L"", WS_VISIBLE | WS_CHILD, 30, 120, 200, 40, hwnd, nullptr, nullptr, nullptr);

}

LRESULT CALLBACK MyWindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){
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
                    else
                        SetWindowText(hWrongValue, "");
                    break;
            } 
            break;

        case WM_KEYDOWN:
            if(wp == VK_ESCAPE)
                PostQuitMessage(0);
            break;
        default:
            return DefWindowProcW(hwnd, msg, wp, lp);
    }
    return 0;
}


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
    //MessageBox(nullptr, "HELLO", "TESTNAME", MB_DEFAULT_DESKTOP_ONLY);

    WNDCLASSW wc = {0};

    wc.hbrBackground = (HBRUSH) COLOR_WINDOW;
    wc.hCursor = LoadCursor(nullptr, IDC_HAND); //IDC_ARROW
    wc.hInstance = hInst;
    wc.lpszClassName = L"myWindowClass";
    wc.lpfnWndProc = MyWindowProcedure;

    if (!RegisterClassW(&wc))
        return -1;

    CreateWindowW(L"myWindowClass", L"WindowName", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 1000, nullptr,
                  nullptr, nullptr, nullptr);

    MSG msg = {nullptr};

    while (GetMessage(&msg, nullptr, NULL, NULL)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        if(kbhit()){
                return -1;
        }

    }



    return 0;
}