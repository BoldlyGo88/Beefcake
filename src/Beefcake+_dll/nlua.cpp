#include "nlua.h"
#include "beefcake.h"
#include "memory.h"
#include <iostream>

uintptr_t noita_base = 0x00400000;
lua_State* L = NULL;
lua_State* unsafeState = NULL;
inline void nlib_hook();
inline void modhook();
DWORD modreturn;

// noitas restricted modding functions
nModDevGenerateSpriteUVsForDirectory ModDevGenerateSpriteUVsForDirectory = NULL;
nModLuaFileAppend ModLuaFileAppend = NULL;
nModMagicNumbersFileAdd ModMagicNumbersFileAdd = NULL;
nModMaterialsFileAdd ModMaterialsFileAdd = NULL;
nModRegisterAudioEventMappings ModRegisterAudioEventMappings = NULL;
nModTextFileGetContent ModTextFileGetContent = NULL;
nModTextFileWhoSetContent ModTextFileWhoSetContent = NULL;
nModTextSetFileContent ModTextSetFileContent = NULL;

// defining these up here to avoid errors & qol, all the code is at the bottom

void nlua_init() {
	ModDevGenerateSpriteUVsForDirectory = (nModDevGenerateSpriteUVsForDirectory)(noita_base + nlua_offsets::moddevspriteuv);
	ModLuaFileAppend = (nModLuaFileAppend)(noita_base + nlua_offsets::modluafileappend);
	ModMagicNumbersFileAdd = (nModMagicNumbersFileAdd)(noita_base + nlua_offsets::modmagicnumbers);
	ModMaterialsFileAdd = (nModMaterialsFileAdd)(noita_base + nlua_offsets::modmaterials);
	ModRegisterAudioEventMappings = (nModRegisterAudioEventMappings)(noita_base + nlua_offsets::modregisteraudio);
	ModTextFileGetContent = (nModTextFileGetContent)(noita_base + nlua_offsets::modtextfilegetcontent);
	ModTextFileWhoSetContent = (nModTextFileWhoSetContent)(noita_base + nlua_offsets::modtextfilewhosetcontent);
	ModTextSetFileContent = (nModTextSetFileContent)(noita_base + nlua_offsets::modtextsetfilecontent);

	simple_hook((void*)(noita_base + nlua_offsets::function_library), nlib_hook, 5);
	int p = 0;
LOOP:
	int addressPTR = *reinterpret_cast<int *>(noita_base + nlua_offsets::mod_api_table);
	if (addressPTR == NULL)
	{
		if (p == 0)
		{
			std::cout << "Hooking mod check.." << std::endl;
			modreturn = (noita_base + nlua_offsets::mod_set_one) + 7;
			simple_hook((void*)(noita_base + nlua_offsets::mod_set_one), modhook, 7);
			Sleep(850);
			std::cout << "Waiting for run to start.." << std::endl;
			p = 1;
		}
		goto LOOP;
	}
	else {
		std::cout << "Run starting.." << std::endl;
		Sleep(1000);
		system("cls");
		std::cout << "Noita Base: " << std::hex << noita_base << std::endl;
		std::cout << "Noita Function Library: " << std::hex << (noita_base + nlua_offsets::function_library) << "\n " << std::endl;
		std::cout << "Lua Base: " << std::hex << lua_base << std::endl;
		std::cout << "Lua State: " << std::hex << L << "\n\n " << std::endl;
	}
}

void __declspec(naked) modhook() {

	__asm {
		mov byte ptr[eax+0x00000120],00
		jmp [modreturn]
	}
}

void __declspec(naked) nlib_hook() {
	__asm {
		mov L, ebx
	}

	if (L != NULL)
	{
		nregister(L, "AddSpellToWand", AddSpellToWand);
		nregister(L, "CreateWand", CreateWand);
		nregister(L, "EditWand", EditWand);
		nregister(L, "EntityGetChild", EntityGetChild);
		nregister(L, "GenomeGetHerdId", GenomeGetHerdId);
		nregister(L, "print", Print); // this may be causing problems.. idk yet
		nregister(L, "SetWorldTime", SetWorldTime);
		nregister(L, "SpawnFlask", SpawnFlask);
		nregister(L, "SpawnPerk", SpawnPerk);
		nregister(L, "SpawnSpell", SpawnSpell);

		nregister(L, "ModDevGenerateSpriteUVsForDirectory", (lua_CFunction)ModDevGenerateSpriteUVsForDirectory);
		nregister(L, "ModLuaFileAppend", (lua_CFunction)ModLuaFileAppend);
		nregister(L, "ModMagicNumbersFileAdd", (lua_CFunction)ModMagicNumbersFileAdd);
		nregister(L, "ModMaterialsFileAdd", (lua_CFunction)ModMaterialsFileAdd);
		nregister(L, "ModRegisterAudioEventMappings", (lua_CFunction)ModRegisterAudioEventMappings);
		nregister(L, "ModTextFileGetContent", (lua_CFunction)ModTextFileGetContent);
		nregister(L, "ModTextFileWhoSetContent", (lua_CFunction)ModTextFileWhoSetContent);
		nregister(L, "ModTextSetFileContent", (lua_CFunction)ModTextSetFileContent);

		vregister(L, pushnumber, "cdd", 0.0165f);
		vregister(L, pushnumber, "inf", 2147483647);
		vregister(L, pushnumber, "rfd", 0.0167f);

		loadstring(L, "input = {}; LocalPlayer = {}; nat = {};");
		if (pcall(L, 0, 0, 0) == 0) {
			getglobal(L, "input");
			if (type(L, -1) == LUA_TTABLE) {
				tregister(L, KeyDown, -2, "KeyDown");
				tregister(L, MouseLeftDown, -2, "LeftMouseDown");
				tregister(L, MouseRightDown, -2, "RightMouseDown");
			};
			getglobal(L, "LocalPlayer");
			if (type(L, -1) == LUA_TTABLE) {
				tregister(L, AddPerk, -2, "AddPerk");
				tregister(L, GetPlayer, -2, "GetId");
				tregister(L, GetIgnored, -2, "GetIsIgnored");
				tregister(L, GetPlayerAir, -2, "GetAir");
				tregister(L, GetPlayerAirM, -2, "GetMaxAir");
				tregister(L, GetPlayerClimb, -2, "GetClimbHeight");
				tregister(L, GetPlayerPos, -2, "GetPosition");
				tregister(L, GetPlayerHealth, -2, "GetHealth");
				tregister(L, GetPlayerHealthM, -2, "GetMaxHealth");
				tregister(L, GetPlayerGold, -2, "GetGold");
				tregister(L, GetPlayerGoldSpent, -2, "GetSpentGold");
				tregister(L, GetPlayerJetpack, -2, "GetJetpack");
				tregister(L, GetPlayerJetpackRecharge, -2, "GetJetpackRecharge");
				tregister(L, GetPlayerNeedsAir, -2, "GetNeedsAir");
				tregister(L, GetPlayerQInventory, -2, "GetInventory");
				tregister(L, GetPlayerStomachFullness, -2, "GetStomachFullness");
				tregister(L, GetPlayerStomachSize, -2, "GetStomachSize");
				tregister(L, IsPolymorphed, -2, "IsPolymorphed");
				tregister(L, SetPlayerAir, -2, "SetAir");
				tregister(L, SetPlayerAirM, -2, "SetMaxAir");
				tregister(L, SetPlayerClimb, -2, "SetClimbHeight");
				tregister(L, SetPlayerPos, -2, "SetPosition");
				tregister(L, SetPlayerHealth, -2, "SetHealth");
				tregister(L, SetPlayerHealthM, -2, "SetMaxHealth");
				tregister(L, SetPlayerGold, -2, "SetGold");
				tregister(L, SetPlayerJetpack, -2, "SetJetpack");
				tregister(L, SetPlayerNeedsAir, -2, "SetNeedsAir");
				tregister(L, SetPlayerStomachFullness, -2, "SetStomachFullness");
				tregister(L, SetPlayerStomachSize, -2, "SetStomachSize");
				tregister(L, SetIgnored, -2, "SetIsIgnored");
			};
			getglobal(L, "nat");
			if (type(L, -1) == LUA_TTABLE) {
				tregister(L, ExecuteThroughLoader, -2, "ExecuteTL");
				tregister(L, GetCFunctionPointer, -2, "GetCFunctionPointer");
				tregister(L, GetState, -2, "GetState");
			};
		};
	}

	__asm {
		pop edi
		pop esi
		pop ebx
		ret
		int 3
	}
}