#include "demofuncs"
#include <windows.h>
#include <utility>
#include "Manager.h"

Manager* manager;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {

   manager = new Manager();

   manager->windowsController(hInst);


    return 0;
}