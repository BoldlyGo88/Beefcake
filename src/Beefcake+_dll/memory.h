#ifndef MEMORY_H
#define MEMORY_H

#include <windows.h>

bool simple_hook(void* target, void* custom, int len) {
	DWORD original;
	VirtualProtect(target, len, 0x40, &original);
	memset(target, 0x90, len);
	DWORD rA = ((DWORD)custom - (DWORD)target) - 5;
	*(BYTE*)target = 0xE9;
	*(DWORD*)((DWORD)target + 1) = rA;
	DWORD tmp;
	VirtualProtect(target, len, original, &tmp);
	return true;
}

#endif