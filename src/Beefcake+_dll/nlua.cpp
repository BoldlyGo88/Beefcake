#include "nlua.h"
#include "beefcake.h"
#include "libmem/libmem.hpp"

uintptr_t noita_base = 0x00400000;
lua_State* state = NULL;
nlib lib = NULL;

// defining these up here to avoid errors & qol, all the code is at the bottom
void writeINT(uintptr_t address, int value);
mem::uintptr_t readPTR(uintptr_t address);

void nlua_init() {
	lib = (nlib)(noita_base + nlua_offsets::function_library);
	lib = (nlib)mem::in::detour_trampoline((mem::voidptr_t)lib, (mem::voidptr_t)nlib_hook, 9, mem::MEM_DT_M1);
	int p = 0;
LOOP:
	uintptr_t address = readPTR(noita_base + nlua_offsets::mod_api_table);
	if (address == NULL)
	{
		if (p == 0)
		{
			std::cout << "Waiting for run to start.." << std::endl;
			p = 1;
		}
		goto LOOP;
	}
	else {
		std::cout << "IsModded found: " << std::hex << address << std::endl;
		std::cout << "Changing mod status.." << std::endl;
		writeINT(noita_base + nlua_offsets::mod_set_ismodding, 786960875);
		writeINT(address + nlua_offsets::mod_ismodding, 0);
		Sleep(1000);
		system("cls");
		std::cout << "Noita Base: " << std::hex << noita_base << std::endl;
		std::cout << "Noita Function Library: " << std::hex << (noita_base + nlua_offsets::function_library) << "\n " << std::endl;
		std::cout << "Lua Base: " << std::hex << lua_base << std::endl;
		std::cout << "Lua State: " << std::hex << state << "\n\n " << std::endl;
	}
}

void __fastcall nlib_hook(lua_State* L) {

	// Initiate input library
	const struct luaL_Reg InputFuncs[] = {
		{"LeftMouseDown", MouseLeftDown},
		{"RightMouseDown", MouseRightDown},
		{NULL, NULL}
	};

	// Initiate LocalPlayer library
	const struct luaL_Reg LocalPlayerFuncs[] = {
			{"AddPerk", AddPerk},
			{"GetID", GetPlayer},
			{"GetIsIgnored", GetIgnored},
			{"GetAir", GetPlayerAir},
			{"GetMaxAir", GetPlayerAirM},
			{"GetClimbHeight", GetPlayerClimb},
			{"GetPosition", GetPlayerPos},
			{"GetHealth", GetPlayerHealth},
			{"GetMaxHealth", GetPlayerHealthM},
			{"GetGold", GetPlayerGold},
			{"GetJetpack", GetPlayerJetpack},
			{"GetJetpackRecharge", GetPlayerJetpackRecharge},
			{"GetNeedsAir", GetPlayerNeedsAir},
			{"GetInventory", GetPlayerQInventory},
			{"GetStomachSize", GetPlayerStomachSize},
			{"SetAir", SetPlayerAir},
			{"SetMaxAir", SetPlayerAirM},
			{"SetClimbHeight", SetPlayerClimb},
			{"SetPosition", SetPlayerPos},
			{"SetHealth", SetPlayerHealth},
			{"SetMaxHealth", SetPlayerHealthM},
			{"SetGold", SetPlayerGold},
			{"SetJetpack", SetPlayerJetpack},
			{"SetNeedsAir", SetPlayerNeedsAir},
			{"SetStomachSize", SetPlayerStomachSize},
			{"SetIsIgnored", SetIgnored},
			{NULL, NULL}
	};

	// Initiate task library
	const struct luaL_Reg taskfuncs[] = {
			{"ExecuteTL", ExecuteThroughLoader},
			{"ForceIBB", ForceIsBetaBuild},
			{"GetCFunctionPointer", GetCFunctionPointer},
			{"GetState", GetState},
			//{"ReadMemory", ReadMemory}, may or not may reimplement this
			{NULL, NULL}
	};

	// Register the libraries
	lregister(L, "input", InputFuncs);
	lregister(L, "LocalPlayer", LocalPlayerFuncs);
	lregister(L, "task", taskfuncs);

	// Register our globals
	nregister(L, "AddSpellToWand", AddSpellToWand);
	nregister(L, "CreateWand", CreateWand);
	nregister(L, "EntityGetChild", EntityGetChild);
	nregister(L, "ForceSeed", ForceSeed);
	nregister(L, "GenomeGetHerdId", GenomeGetHerdId);
	nregister(L, "print", Print);
	nregister(L, "SetWorldTime", SetWorldTime);
	nregister(L, "SpawnFlask", SpawnFlask);
	nregister(L, "SpawnPerk", SpawnPerk);
	nregister(L, "SpawnSpell", SpawnSpell);

	vregister(L, pushnumber, "inf", 2147483647);
	
	luaopen_bit(L);
	luaopen_debug(L);
	luaopen_ffi(L);
	luaopen_io(L);
	luaopen_jit(L);
	luaopen_os(L);

	state = L;
	return lib(L);
}

// function to read a pointer from an address
mem::uintptr_t readPTR(uintptr_t address)
{
	// value to store our pointer
	mem::uintptr_t value = 0;
	mem::prot_t original_protection = mem::in::get_page((mem::voidptr_t)address).protection;
	mem::in::protect((mem::voidptr_t)address, (mem::size_t)(mem::voidptr_t)address, PAGE_EXECUTE_READWRITE);
	if (mem::in::get_page((mem::voidptr_t)address).protection == original_protection)
	{
		// again, we need to use VirtualProtectEx
		mem::process_t proc = mem::ex::get_process(GetCurrentProcessId());
		mem::ex::protect(proc, (mem::voidptr_t)address, (mem::size_t)(mem::voidptr_t)address, PAGE_EXECUTE_READWRITE);
		// lets get the pointer value from the address
		value = mem::ex::read<mem::uintptr_t>(proc, (mem::voidptr_t)address);
		mem::ex::protect(proc, (mem::voidptr_t)address, (mem::size_t)(mem::voidptr_t)address, original_protection);
	}
	else {
		// lets get the pointer value from the address
		value = mem::in::read<mem::uintptr_t>((mem::voidptr_t)address);
		mem::in::protect((mem::voidptr_t)address, (mem::size_t)(mem::voidptr_t)address, original_protection);
	}
	// return the pointer address
	return value;
}

// function to write an integer to address value
// uncommented, explained twice already in readPTR, and writeAOB
void writeINT(uintptr_t address, int value)
{
	mem::prot_t original_protection = mem::in::get_page((mem::voidptr_t)address).protection;
	mem::in::protect((mem::voidptr_t)address, (mem::size_t)(mem::voidptr_t)address, PAGE_EXECUTE_READWRITE);
	if (mem::in::get_page((mem::voidptr_t)address).protection == original_protection)
	{
		mem::process_t proc = mem::ex::get_process(GetCurrentProcessId());
		mem::ex::protect(proc, (mem::voidptr_t)address, (mem::size_t)(mem::voidptr_t)address, PAGE_EXECUTE_READWRITE);
		mem::ex::write<mem::int32_t>(proc, (mem::voidptr_t)address, (mem::int32_t)value);
		mem::ex::protect(proc, (mem::voidptr_t)address, (mem::size_t)(mem::voidptr_t)address, original_protection);
	}
	else {
		mem::in::write<mem::int32_t>((mem::voidptr_t)address, (mem::int32_t)value);
		mem::in::protect((mem::voidptr_t)address, (mem::size_t)(mem::voidptr_t)address, original_protection);
	}
}
