/**
 * 3nd Course IPS-32
 * Lab 1.
 *
 * Purpose : Create manager struct and auxiliary functions.
 *
 * @author Vitaliy Datsiuk
 * @version 1 02/10/20
 */

#ifndef LAB1_MANAGER_H
#define LAB1_MANAGER_H

#define FUNCTION_PATH R"(D:\University\3rd Course\OperationSystems\OperationSystems\Lab1\Functions\cmake-build-debug\Functions.exe)"
#define GET_TEXT 1
#define GET_RESULT 1
#define GET_RESULT_DEMO 2

#define DEMOFUNC_1 2
#define DEMOFUNC_2 3
#define DEMOFUNC_3 4
#define DEMOFUNC_4 5
#define DEMOFUNC_5 6
#define DEMOFUNC_6 7

#include <thread>
#include <windows.h>
#include <vector>
#include <iostream>
#include "Utils.h"

/**
 * This structure is used to store the value to be passed by computation processes
 */
typedef struct{
    int xResult;
    char func;
} RESULT;

/**
 * This class initialize computation process, computes the final result and organizes cancellation.
 */
class Manager {
private:
    /** @brief Holds the values of functions computation */
    int fx, gx;

    /** @brief Holds the converted int value of input */
    int *inputValueInt;                                                                      ////

    /** @brief Holds the values whether functions were computed */
    bool fIsFinished, gIsFinished;

    /** @brief Holds the handlers for windows */
    HWND hInputWindow, hWrongValueLabel, hFxLabel, hGxLabel, hBinaryResultLabel, hComputeButton, hErrorLabel;      ////

    HWND hDemoFuncsButtons[6];
    /** @brief Holds the process information variables of the computing processes */
    std::vector<PROCESS_INFORMATION> processInfArr;

    /** @brief Holds the variable that store all the information about passed data by computation processes */
    PCOPYDATASTRUCT pCopyDataStruct;

    /**
     * @brief register and creates the main window
     * @param hInst window descriptor
     * @return whether the window was created
     */
    static bool createMainWindow(HINSTANCE hInst);

    /**
     * @brief register and creates the hidden window
     * @param hInst window descriptor
     * @return whether the window was created
     */
    static bool createHiddenWindow(HINSTANCE hInst);



public:
    Manager();

    [[nodiscard]] bool isFIsFinished() const;

    [[nodiscard]] bool isGIsFinished() const;

    [[nodiscard]] int getFx() const;

    [[nodiscard]] int getGx() const;

    int *getInputValueInt();

    HWND getHInputWindow();

    HWND getHWrongValueLabel();

    HWND getHFxLabel();

    HWND getHGxLabel();

    HWND getHErrorLabel();

    HWND getHBinaryResultLabel();

    HWND getHComputeButton();

    PCOPYDATASTRUCT getPCopyDataStruct() ;

    HWND *getHDemoFuncsButtons();

    void setPCopyDataStruct(PCOPYDATASTRUCT pCopyDataStruct);

    void setInputValueInt(int *inputValueInt);

    /**
     * @brief calls main and hidden window creators
     * @param hInst window descriptor
     * @return whether the windows were created
     */
    static bool createWindows(HINSTANCE hInst);

    /**
     * @brief store the func process result into a class variables
     * @param xResult result of f(x) or of g(x)
     * @param func determines the func f or g
     */
    void writeFuncResult(int xResult, char func);

    /**
     * @brief terminates processes for functions f and g
     */
    void terminateChildProcesses();

    /**
     * @brief creates a process for g or f function that evaluates the value from input x
     * @param exePath path of the function process
     * @param funcName could be f, g or b(for binary func)
     * @param x input value
     * @return whether the process where created
     */
    bool evaluateFuncProc(LPCTSTR exePath, std::string funcName, int x);                ////

    /**
     * @brief creates a process for binary func that evaluates f(x) * g(x)
     * @param exePath path of the binary function process
     * @param funcName determines binary func in the process
     * @param fxVal value of f(x)
     * @param gxVal value of g(x)
     * @return whether the process where created
     */
    static bool evaluateBinaryProc(LPCTSTR exePath, std::string funcName, int fxVal, int gxVal);

    /**
     * @brief reset the func process result from a class variables
     */
    void resetFuncResults();

    /**
     * @brief reset info labels from main window
     */
    void resetLabels();

    /**
     * @brief calls evaluateFuncProc() for functions f and g
     * @param x the input value
     * @return whether processes were created
     */
    bool callFunctions(int x);

    bool callDemoFunctions(int x);

    /**
     * @brief adds labels and button on the main window
     * @param hwnd main window handler
     */
    void addControls(HWND hwnd);

    /**
     * @brief process the input messages for both windows
     * @param hInst main window descriptor
     */
    static void windowsController(HINSTANCE hInst);

    void disableButtons();

    void enableButtons();

};

extern Manager* manager;

/**
* @brief window procedure func for hidden window
* @param hwnd a handle to the hidden window
* @param msg message to process
* @param wp additional message information
* @param lp additional message information
* @return
*/
LRESULT CALLBACK hiddenWindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

/**
 * @brief window procedure func for main window
 * @param hwnd window procedure func for main window
 * @param msg msg message to process
 * @param wp additional message information
 * @param lp additional message information
 * @return
 */
LRESULT CALLBACK mainWindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);


#endif //LAB1_MANAGER_H
