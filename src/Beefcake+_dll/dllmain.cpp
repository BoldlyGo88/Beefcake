#include "nlua.h"
#include <cstdio>
#include <iostream>
#include <string>

DWORD WINAPI Beefcake_Init(LPVOID lpReserved)
{
    // lets create our console and rework outputs
    AllocConsole();
    SetConsoleTitleA("Beefcake Console");
    FILE* fptr;
    freopen_s(&fptr, "CONIN$", "r", stdin);
    freopen_s(&fptr, "CONOUT$", "w", stderr);
    freopen_s(&fptr, "CONOUT$", "w", stdout);

    hlua_init();
    nlua_init();
BACK:
    std::string debug_command;
    std::getline(std::cin, debug_command);
    if (debug_command == "test")
    {
        getfield(L, LUA_GLOBALSINDEX, "GamePrintImportant");
        pushstring(L, "TEST MESSAGE");
        pushstring(L, "Sent through console!");
        pcall(L, 2, 0, 0);

        goto BACK;
    }
    else {
        loadstring(L, debug_command.c_str());
        pcall(L, 0, -1, 0);
        goto BACK;
    }
    goto BACK;
    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        CreateThread(NULL, 0, Beefcake_Init, NULL, 0, NULL);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}