#include <Windows.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>

void noitamadness()
{
    // information for CreateProcessA
    STARTUPINFOA sInfo;
    PROCESS_INFORMATION pInfo;

    // paths
    LPCSTR bcDll = "beefcake\\beefer.dll";
    std::string path;
    std::string ogpath = std::filesystem::current_path().generic_string();

    // make sure both struct sInfo and pInfo are fresh, all 0
    ZeroMemory(&sInfo, sizeof(sInfo));
    sInfo.cb = sizeof(sInfo);
    ZeroMemory(&pInfo, sizeof(pInfo));

    // check if beefconfig.txt exists (first time running program or not)
    if (!std::filesystem::exists("beefconfig.txt"))
    {
        std::cout << "It seems to be your first time running beefcake, please enter Noita's directory!" << std::endl;
        std::getline(std::cin, path);
        std::cout << "[BEEF] " << "Noita's path set to: " << path << std::endl;
        if (std::filesystem::exists(path + "\\noita.exe"))
        {
            std::cout << "[BEEF] " << "noita.exe located!" << std::endl;
            std::cout << "Setting up files.." << std::endl;
            // save path for future uses
            std::ofstream beefconfig("beefconfig.txt");
            beefconfig << path << std::endl;
            beefconfig.close();
            std::cout << "[BEEF] " << "beefconfig.txt created!" << std::endl;
        }
        else
        {
            std::cout << "[BEEF] " << "noita.exe not found, aborting!" << std::endl;
            std::cin.get();
            return;
        }
        // check if in correct path, then set current directory and append noita.exe
        if (std::filesystem::exists(path + "\\noita.exe"))
        {
            SetCurrentDirectoryA(path.c_str());
            path = path + "\\noita.exe";
        }
    }
    else {
        std::ifstream beefconfig("beefconfig.txt");
        std::getline(beefconfig, path);
        beefconfig.close();
        // check if in correct path, then set current directory and append noita.exe
        if (std::filesystem::exists(path + "\\noita.exe"))
        {
            SetCurrentDirectoryA(path.c_str());
            path = path + "\\noita.exe";
        }
    }

    // create noita.exe process
    CreateProcessA(path.c_str(), __argv[1], NULL, NULL, FALSE, NULL, NULL, NULL, &sInfo, &pInfo);
    // change the path back to beefcake/
    SetCurrentDirectoryA(ogpath.c_str());
    Sleep(900);

    // get the process id of noita.exe and open the process
    DWORD pID = pInfo.dwProcessId;
    HANDLE nHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);

    // allocate memory for the beefer.dll, check if allocated, then write the .dll
    LPVOID aDll = VirtualAllocEx(nHandle, 0, strlen(bcDll) + 1, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    if (!aDll) return;
    WriteProcessMemory(nHandle, aDll, (LPVOID)bcDll, strlen(bcDll) + 1, 0);

    // get the module for Kernel32.dll
    HMODULE kHandle = GetModuleHandleA("Kernel32.dll");
    if (!kHandle) return;

    // create a remote thread and execute LoadLibraryA from Kernel32.dll
    HANDLE rThread = CreateRemoteThread(nHandle, 0, 0, (LPTHREAD_START_ROUTINE)GetProcAddress(kHandle, "LoadLibraryA"), aDll, 0, 0);
    if (!rThread) return;

    // wait for the thread to finish
    WaitForSingleObject(rThread, INFINITE);

    // free up everything
    VirtualFreeEx(nHandle, aDll, 0, MEM_RELEASE);
    CloseHandle(pInfo.hProcess);
    CloseHandle(pInfo.hThread);
}

int main()
{
    SetConsoleTitleA("Beefcake Init Console");
    noitamadness();
}