#ifndef N_LUA_H
#define N_LUA_H

#include "hlua.h"


typedef void(__fastcall* nlib)(lua_State* L);

extern nlib lib;

extern uintptr_t noita_base;
extern lua_State* state;

void nlua_init();
void __fastcall nlib_hook(lua_State* L);
void writeINT(uintptr_t address, int value);

enum nlua_offsets {
	function_library = 0x31BF20,
	isbetabuild = 0xB41074,
	mod_api_table = 0xBF5A54,
	mod_ismodding = 0x00000120,
	mod_set_ismodding = 0x2429DB,
	world_seed = 0xBF5A48
};
#endif