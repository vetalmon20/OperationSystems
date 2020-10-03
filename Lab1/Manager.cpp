/**
 * 3nd Course IPS-32
 * Lab 1.
 *
 * Purpose : Create manager struct.
 *
 * @author Vitaliy Datsiuk
 * @version 1 02/10/20
 */

#include "Manager.h"

using namespace std;

Manager::Manager() {
    this->fIsFinished = false;
    this->gIsFinished = false;

    this->inputValueInt = nullptr;
}

bool Manager::evaluateFuncProc(LPCTSTR exePath, std::string funcName, int x) {
    string xStr = std::to_string(x);
    string params = std::move(funcName);
    params += " ";
    params += xStr;
    std::vector<char> paramsCharTemp(params.c_str(), params.c_str() + params.size() + 1);
    CHAR *paramsChar = reinterpret_cast<char*>(paramsCharTemp.data());

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

    this->processInfArr.push_back(pi);

    return true;
}

bool Manager::evaluateBinaryProc(LPCTSTR exePath, std::string funcName, int fxVal, int gxVal) {
    string fxStr = std::to_string(fxVal);
    string gxStr = std::to_string(gxVal);
    string params = std::move(funcName);
    params += " ";
    params += fxStr;
    params += " ";
    params += gxStr;
    std::vector<char> paramsCharTemp(params.c_str(), params.c_str() + params.size() + 1);
    CHAR *paramsChar = reinterpret_cast<char*>(paramsCharTemp.data());

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

void Manager::terminateChildProcesses() {
    for(auto & i : this->processInfArr){
        if(!TerminateProcess(i.hProcess, 0))
            continue;
        if(!CloseHandle(i.hProcess))
            continue;
        if(!CloseHandle(i.hThread))
            continue;

        i.hProcess = i.hThread = nullptr;
    }

    this->processInfArr.clear();

    //cout << "PROCESS WERE TERMINATED" << endl;

}

void Manager::addControls(HWND hwnd) {
    CreateWindowW(L"static", L"Enter the value of x:",
                  WS_VISIBLE | WS_CHILD,  30, 100, 150, 20, hwnd, nullptr, nullptr, nullptr);

    this->hInputWindow = CreateWindowW(L"edit", L"",
                                       WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL, 200, 100,
                                       150, 20, hwnd, nullptr, nullptr, nullptr);

    this->hComputeButton = CreateWindowW(L"button", L"Execute!",
                                         WS_VISIBLE | WS_CHILD, 100, 200,
                                         200, 100, hwnd, (HMENU)GET_TEXT, nullptr, nullptr);

    this->hWrongValueLabel = CreateWindowW(L"static", L"",
                                           WS_VISIBLE | WS_CHILD, 30, 120,
                                           200, 40, hwnd, nullptr, nullptr, nullptr);

    CreateWindowW(L"static", L"f(x) result:",
                  WS_VISIBLE | WS_CHILD,  30, 400, 100, 20, hwnd, nullptr, nullptr, nullptr);

    CreateWindowW(L"static", L"g(x) result:",
                  WS_VISIBLE | WS_CHILD,  160, 400, 100, 20, hwnd, nullptr, nullptr, nullptr);

    this->hFxLabel = CreateWindowW(L"static", L"",
                                   WS_VISIBLE | WS_CHILD,  30, 420,
                                   100, 20, hwnd, nullptr, nullptr, nullptr);

    this->hGxLabel = CreateWindowW(L"static", L"",
                                   WS_VISIBLE | WS_CHILD,  160, 420,
                                   100, 20, hwnd, nullptr, nullptr, nullptr);

    CreateWindowW(L"static", L"RESULT:",
                  WS_VISIBLE | WS_CHILD,  100, 540, 100, 20, hwnd, nullptr, nullptr, nullptr);

    this->hBinaryResultLabel = CreateWindowW(L"static", L"",
                                             WS_VISIBLE | WS_CHILD,  100, 570,
                                             100, 20, hwnd, nullptr, nullptr, nullptr);

    this->hErrorLabel = CreateWindowW(L"static", L"",
                                      WS_VISIBLE | WS_CHILD,  120, 600,
                                      300, 20, hwnd, nullptr, nullptr, nullptr);

}

void Manager::writeFuncResult(int xResult, char func) {

    if(func == 'f'){
        this->fx = xResult;
        this->fIsFinished = true;
    }

    if(func == 'g'){
        this->gx = xResult;
        this->gIsFinished = true;
    }
}

void Manager::resetFuncResults() {
    this->fIsFinished = false;
    this->gIsFinished = false;
}

void Manager::resetLabels() {
    SetWindowText(this->hBinaryResultLabel, "");
    SetWindowText(this->hFxLabel, "");
    SetWindowText(this->hGxLabel, "");
}

LRESULT CALLBACK hiddenWindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {

    switch(msg){
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_CREATE:
            //addControls(hwnd);
            break;
        case WM_COPYDATA:
            manager->setPCopyDataStruct((PCOPYDATASTRUCT) lp);
            switch(manager->getPCopyDataStruct()->dwData){
                case GET_RESULT:
                    if(manager->isFIsFinished() && manager->isGIsFinished()){

                        string xResult = std::to_string(((RESULT *)(manager->getPCopyDataStruct()->lpData))->xResult);
                        SetWindowText(manager->getHBinaryResultLabel(), xResult.c_str());

                        EnableWindow(manager->getHComputeButton(), true);
                        EnableWindow(manager->getHInputWindow(), true);

                    } else {
                        manager->writeFuncResult(((RESULT *)(manager->getPCopyDataStruct()->lpData))->xResult,
                                        ((RESULT *)(manager->getPCopyDataStruct()->lpData))->func);

                        if(((RESULT *)(manager->getPCopyDataStruct()->lpData))->func == 'g'){
                            string xResult = std::to_string(((RESULT *)(manager->getPCopyDataStruct()->lpData))->xResult);
                            SetWindowText(manager->getHGxLabel(), xResult.c_str());

                            if(((RESULT *)(manager->getPCopyDataStruct()->lpData))->xResult == 0){
                                manager->terminateChildProcesses();

                                EnableWindow(manager->getHComputeButton(), true);
                                EnableWindow(manager->getHInputWindow(), true);
                                SetWindowText(manager->getHFxLabel(), "Undefined");
                                SetWindowText(manager->getHBinaryResultLabel(), "0");
                                SetWindowText(manager->getHErrorLabel(), "Calculation was terminated (zero value)");
                            }


                            if(manager->isFIsFinished()){
                                manager->evaluateBinaryProc(FUNCTION_PATH, "b", manager->getFx(), manager->getGx());
                            }

                        }

                        if(((RESULT *)(manager->getPCopyDataStruct()->lpData))->func == 'f'){
                            string xResult = std::to_string(((RESULT *)(manager->getPCopyDataStruct()->lpData))->xResult);
                            SetWindowText(manager->getHFxLabel(), xResult.c_str());

                            if(((RESULT *)(manager->getPCopyDataStruct()->lpData))->xResult == 0){
                                manager->terminateChildProcesses();

                                EnableWindow(manager->getHComputeButton(), true);
                                EnableWindow(manager->getHInputWindow(), true);
                                SetWindowText(manager->getHGxLabel(), "Undefined");
                                SetWindowText(manager->getHBinaryResultLabel(), "0");
                                SetWindowText(manager->getHErrorLabel(), "Calculation was terminated (zero value)");
                            }

                            if(manager->isGIsFinished()){
                                manager->evaluateBinaryProc(FUNCTION_PATH, "b", manager->getFx(), manager->getGx());
                            }
                        }
                    }

                    break;
            }
            break;

        case WM_KEYDOWN:
            if(wp == VK_ESCAPE){
                cout << "PRESSED HIDDEN WINDOW BUTTON";
            }
            break;
        default:
            return DefWindowProcW(hwnd, msg, wp, lp);
    }
    return 0;
}

LRESULT CALLBACK mainWindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch(msg){
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_CREATE:
            manager->addControls(hwnd);     ////
            break;
        case WM_COMMAND:
            switch(wp){
                case GET_TEXT:
                    char text[100];
                    GetWindowText(manager->getHInputWindow(), text, 100);

                    manager->setInputValueInt(Utils::isInteger(text));
                    if(!Utils::isInteger(text))
                        SetWindowText(manager->getHWrongValueLabel(), "Wrong value!");
                    else{
                        SetFocus(hwnd);
                        manager->resetFuncResults();
                        manager->resetLabels();                                                          ////////////////////

                        manager->callFunctions(*(manager->getInputValueInt()));
                        SetWindowText(manager->getHWrongValueLabel(), "");
                        SetWindowText(manager->getHErrorLabel(), "");
                        EnableWindow(manager->getHComputeButton(), false);
                        EnableWindow(manager->getHInputWindow(), false);
                    }
                    break;
            }
            break;

        case WM_KEYDOWN:
            if(wp == VK_ESCAPE){
                cout << "PRESSED ";
                manager->terminateChildProcesses();

                if(!IsWindowEnabled(manager->getHComputeButton()))
                    SetWindowText(manager->getHErrorLabel(), "Calculation was terminated by pressing esc");

                if(!manager->isFIsFinished() && !IsWindowEnabled(manager->getHComputeButton()))
                    SetWindowText(manager->getHFxLabel(), "Undefined");

                if(!manager->isGIsFinished() && !IsWindowEnabled(manager->getHComputeButton()))
                    SetWindowText(manager->getHGxLabel(), "Undefined");

                EnableWindow(manager->getHComputeButton(), true);
                EnableWindow(manager->getHInputWindow(), true);
            }

            break;
        default:
            return DefWindowProcW(hwnd, msg, wp, lp);
    }
    return 0;
}

bool Manager::callFunctions(int x) {
    if(!evaluateFuncProc(FUNCTION_PATH, "f", x))
        return false;
    if(!evaluateFuncProc(FUNCTION_PATH, "g", x))
        return false;

    return true;
}

bool Manager::createWindows(HINSTANCE hInst) {
    if(createMainWindow(hInst) && createHiddenWindow(hInst))
        return true;

    return false;
}

bool Manager::createMainWindow(HINSTANCE hInst) {

    WNDCLASSW wc = {0, mainWindowProcedure, 0, 0, hInst,
                    nullptr, LoadCursor(nullptr,IDC_ARROW),(HBRUSH) COLOR_WINDOW,
                    nullptr, L"myWindowClass"};



    if (!RegisterClassW(&wc))
        return -1;

    if(CreateWindowW(L"myWindowClass", L"WindowName", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 1000, nullptr,
                  nullptr, nullptr, nullptr))
        return true;
    else
        return false;
}

bool Manager::createHiddenWindow(HINSTANCE hInst) {
    WNDCLASSW hiddenWindow = {0, hiddenWindowProcedure, 0, 0, hInst,
                              nullptr, nullptr,(HBRUSH) COLOR_WINDOW,
                              nullptr, L"hiddenWindowClass"};

    if (!RegisterClassW(&hiddenWindow))
        return -1;

    if(CreateWindowW(L"hiddenWindowClass", L"hiddenWindow", WS_OVERLAPPEDWINDOW | SW_HIDE, 800, 100, 100, 100, nullptr,
                  nullptr, nullptr, nullptr))
        return true;
    else
        return false;
}

bool Manager::isFIsFinished() const {
    return this->fIsFinished;
}

bool Manager::isGIsFinished() const {
    return this->gIsFinished;
}

HWND Manager::getHBinaryResultLabel() {
    return this->hBinaryResultLabel;
}

HWND Manager::getHComputeButton() {
    return this->hComputeButton;
}

PCOPYDATASTRUCT Manager::getPCopyDataStruct() {
    return this->pCopyDataStruct;
}

void Manager::setPCopyDataStruct(PCOPYDATASTRUCT pCopyDataStruct_) {
    Manager::pCopyDataStruct = pCopyDataStruct_;
}

void Manager::setInputValueInt(int *inputValueInt_) {
    Manager::inputValueInt = inputValueInt_;
}

int Manager::getFx() const {
    return fx;
}

int Manager::getGx() const {
    return gx;
}

int *Manager::getInputValueInt() {
    return inputValueInt;
}

HWND Manager::getHInputWindow() {
    return hInputWindow;
}

HWND Manager::getHWrongValueLabel() {
    return hWrongValueLabel;
}

HWND Manager::getHFxLabel() {
    return hFxLabel;
}

HWND Manager::getHGxLabel() {
    return hGxLabel;
}

HWND Manager::getHErrorLabel() {
    return hErrorLabel;
}

void Manager::windowsController(HINSTANCE hInst) {
    createWindows(hInst);

    MSG msg = {nullptr};

    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}