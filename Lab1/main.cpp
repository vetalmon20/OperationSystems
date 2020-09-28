#include <iostream>
#include "demofuncs"
#include "thread"
#include <windows.h>
#include <string>
#include <vector>

using namespace std;

#define GET_TEXT 1

HWND hEdit;

static string utf16ToUTF8( const wstring &s )
{
    const int size = ::WideCharToMultiByte( CP_UTF8, 0, s.c_str(), -1, nullptr, 0, nullptr, nullptr );

    vector<char> buf( size );
    ::WideCharToMultiByte( CP_UTF8, 0, s.c_str(), -1, &buf[0], size, nullptr, nullptr );

    return string( &buf[0] );
}

void addControls(HWND hwnd){
    CreateWindowW(L"static", L"Enter the value of x:", WS_VISIBLE | WS_CHILD,  30, 100, 150, 20, hwnd, nullptr, nullptr, nullptr);
    hEdit = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL, 200, 100, 150, 20, hwnd, nullptr, nullptr, nullptr);
    CreateWindowW(L"button", L"Execute!", WS_VISIBLE | WS_CHILD, 100, 200, 200, 100, hwnd, (HMENU)GET_TEXT, nullptr, nullptr);

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
                    wchar_t text[100];
                    GetWindowTextW(hEdit, text, 100);

                    std::string utf8String = utf16ToUTF8(text);
                    LPSTR lpStr = const_cast<LPSTR>(utf8String.c_str());
                    MessageBox(hwnd, "TEST", lpStr, MB_OK);
                    break;
            }
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
    }

    return 0;
}