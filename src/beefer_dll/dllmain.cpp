#include <windows.h>
#include "luahook.h"
#include <TlHelp32.h>
#include <fcntl.h>
#include <string>

// should probably rename this from Test, but i don't see a point
DWORD WINAPI Test(LPVOID lpReserved)
{
    // lets create our console and rework outputs
    AllocConsole();
    SetConsoleTitleA("Beefcake Console");
    FILE* fptr;
    freopen_s(&fptr, "CONIN$", "r", stdin);
    freopen_s(&fptr, "CONOUT$", "w", stderr);
    freopen_s(&fptr, "CONOUT$", "w", stdout);

    // lets init everything
    luahook::luahook_init();
BACK:
    // i know im not proud
    std::string piss;
    std::getline(std::cin, piss);
    if (piss == "test") {
        // little debug command, may add more useful ones in the future
        luahook::lua::lua_getfield(luahook::noita::first, LUA_GLOBALSINDEX, "GamePrintImportant");
        luahook::lua::lua_pushstring(luahook::noita::first, "TEST MESSAGE");
        luahook::lua::lua_pushstring(luahook::noita::first, "This is a test message.");
        luahook::lua::lua_pcall(luahook::noita::first, 2, 0, 0);
        goto BACK;
    }
    else if (piss == "current_state") {
        std::cout << std::hex << (int)luahook::noita::first << std::endl;
        goto BACK;
    }
    else {
        luahook::lua::luaL_loadstring(luahook::noita::first, piss.c_str());
        luahook::lua::lua_pcall(luahook::noita::first, 0, -1, 0);
        goto BACK;
    }
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
        CreateThread(NULL, 0, Test, NULL, 0, NULL);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
