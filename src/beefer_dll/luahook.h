#pragma once
#include <windows.h>
#include <iostream>

// these are ripped directly from the lua(jit) 5.1 source, with the exception of lua_registerV
#define LUA_REGISTRYINDEX	(-10000)
#define LUA_ENVIRONINDEX	(-10001)
#define LUA_GLOBALSINDEX	(-10002)
#define LUA_YIELD	1
#define LUA_ERRRUN	2
#define LUA_ERRSYNTAX	3
#define LUA_ERRMEM	4
#define LUA_ERRERR	5
#define LUA_OK			0
#define LUA_TNONE		(-1)
#define LUA_TNIL		0
#define LUA_TBOOLEAN		1
#define LUA_TLIGHTUSERDATA	2
#define LUA_TNUMBER		3
#define LUA_TSTRING		4
#define LUA_TTABLE		5
#define LUA_TFUNCTION		6
#define LUA_TUSERDATA		7
#define LUA_TTHREAD		8
#define LUA_NUMTYPES		9
#define LUA_QL(x)	"'" x "'"
#define lua_register(L,n,f) (lua_pushcfunction(L, (f)), lua_setglobal(L, (n)))
#define lua_registerV(L,t,n,v) (t(L, v), lua_setglobal(L, n))
#define lua_pushcfunction(L,f)	luahook::lua::lua_pushcclosure(L, (f), 0)
#define lua_setglobal(L,s)	luahook::lua::lua_setfield(L, LUA_GLOBALSINDEX, (s))
#define lua_getglobal(L,s)	luahook::lua::lua_getfield(L, LUA_GLOBALSINDEX, (s))
#define lua_pop(L,n)		luahook::lua::lua_settop(L, -(n)-1)
#define lua_newtable(L)		luahook::lua::lua_createtable(L, 0, 0)

class luahook {
public:

	class lua {
	public:
		// defining lua(jit) 5.1 functions, for the most part directly ripped from lua(jit) 5.1 source
		typedef struct lua_State lua_State;
		typedef int(__cdecl* lua_CFunction)(lua_State* L);
		typedef struct luaL_Reg { const char* name; lua_CFunction func; } luaL_Reg;
		typedef double lua_Number;
		typedef ptrdiff_t lua_Integer;
		typedef void(__cdecl* lua51_call)(lua_State* L, int nargs, int nresults);
		typedef void(__cdecl* lua51_createtable)(lua_State* L, int narr, int nrec);
		typedef int(__cdecl* luaL51_error)(lua_State* L, const char* fmt, ...);
		typedef void(__cdecl* lua51_getfield)(lua_State* L, int idx, const char* k);
		typedef int(__cdecl* lua51_getmetatable)(lua_State* L, int index);
		typedef int(__cdecl* lua51_gettop)(lua_State* L);
		typedef int(__cdecl* lua51_iscfunction)(lua_State* L, int idx);
		typedef int(__cdecl* lua51_isnumber)(lua_State* L, int idx);
		typedef int(__cdecl* lua51_isstring)(lua_State* L, int idx);
		typedef void(__cdecl* luaL51_loadstring)(lua_State* L, const char* s);
		typedef int(__cdecl* luaL51_newmetatable)(lua_State* L, const char* tname);
		typedef lua_State*(__cdecl* luaL51_newstate)(void);
		typedef lua_State*(__cdecl* lua51_newthread)(lua_State* L);
		typedef int(__cdecl* lua51_next)(lua_State* L, int index);
		typedef size_t(__cdecl* lua51_objlen)(lua_State* L, int index);
		typedef int(__cdecl* lua51_pcall)(lua_State* L, int nargs, int nresults, int errfunc);
		typedef void(__cdecl* lua51_pushboolean)(lua_State* L, int b);
		typedef void(__cdecl* lua51_pushcclosure)(lua_State* L, lua_CFunction f, int n);
		typedef void(__cdecl* lua51_pushinteger)(lua_State* L, lua_Integer n);
		typedef void(__cdecl* lua51_pushnil)(lua_State* L);
		typedef void(__cdecl* lua51_pushnumber)(lua_State* L, lua_Number n);
		typedef void(__cdecl* lua51_pushstring)(lua_State* L, const char* str);
		typedef void(__cdecl* lua51_pushvalue)(lua_State* L, int idx);
		typedef void(__cdecl* lua51_rawgeti)(lua_State* L, int idx, int n);
		typedef int(__cdecl* luaL51_ref)(lua_State* L, int t);
		typedef void(__cdecl* luaL51_register)(lua_State* L, const char* libname, const luaL_Reg* l);
		typedef int(__cdecl* lua51_resume)(lua_State* L, int narg);
		typedef void(__cdecl* lua51_setfield)(lua_State* L, int idx, const char* k);
		typedef void(__cdecl* lua51_setmetatable)(lua_State* L, int index);
		typedef void(__cdecl* lua51_settable)(lua_State* L, int index);
		typedef void(__cdecl* lua51_settop)(lua_State* L, int idx);
		typedef int(__cdecl* lua51_toboolean)(lua_State* L, int idx);
		typedef lua_CFunction(__cdecl* lua51_tocfunction)(lua_State* L, int idx);
		typedef lua_Integer(__cdecl* lua51_tointeger)(lua_State* L, int idx);
		typedef const char* (__cdecl* lua51_tolstring)(lua_State* L, int idx, size_t* len);
		typedef lua_Number(__cdecl* lua51_tonumber)(lua_State* L, int idx);
		typedef int(__cdecl* lua51_type)(lua_State* L, int index);
		typedef void(__cdecl* luaL51_unref)(lua_State* L, int t, int ref);
		typedef void(__cdecl* lua51_xmove)(lua_State* from, lua_State* to, int n);

		// defining lua(jit) 5.1 library init functions, for the most part directly ripped from lua(jit) 5.1 source
		typedef void(__cdecl* lib51_bit)(lua_State* L);
		typedef void(__cdecl* lib51_debug)(lua_State* L);
		typedef void(__cdecl* lib51_ffi)(lua_State* L);
		typedef void(__cdecl* lib51_io)(lua_State* L);
		typedef void(__cdecl* lib51_jit)(lua_State* L);
		typedef void(__cdecl* lib51_os)(lua_State* L);

		// pointers to all the defined lua functions from above
		inline static uintptr_t luabase;
		inline static uintptr_t call_a;
		inline static uintptr_t createtable_a;
		inline static uintptr_t error_a;
		inline static uintptr_t getfield_a;
		inline static uintptr_t getmetatable_a;
		inline static uintptr_t gettop_a;
		inline static uintptr_t iscfunction_a;
		inline static uintptr_t isnumber_a;
		inline static uintptr_t isstring_a;
		inline static uintptr_t loadstring_a;
		inline static uintptr_t newmetatable_a;
		inline static uintptr_t newstate_a;
		inline static uintptr_t newthread_a;
		inline static uintptr_t next_a;
		inline static uintptr_t objlen_a;
		inline static uintptr_t pcall_a;
		inline static uintptr_t pushboolean_a;
		inline static uintptr_t pushcclosure_a;
		inline static uintptr_t pushinteger_a;
		inline static uintptr_t pushnil_a;
		inline static uintptr_t pushnumber_a;
		inline static uintptr_t pushstring_a;
		inline static uintptr_t pushvalue_a;
		inline static uintptr_t rawgeti_a;
		inline static uintptr_t ref_a;
		inline static uintptr_t register_a;
		inline static uintptr_t resume_a;
		inline static uintptr_t setfield_a;
		inline static uintptr_t setmetatable_a;
		inline static uintptr_t settable_a;
		inline static uintptr_t settop_a;
		inline static uintptr_t toboolean_a;
		inline static uintptr_t tocfunction_a;
		inline static uintptr_t tointeger_a;
		inline static uintptr_t tolstring_a;
		inline static uintptr_t tonumber_a;
		inline static uintptr_t type_a;
		inline static uintptr_t unref_a;
		inline static uintptr_t xmove_a;

		// pointers to all the define library functions from above
		inline static uintptr_t bit_a;
		inline static uintptr_t debug_a;
		inline static uintptr_t ffi_a;
		inline static uintptr_t io_a;
		inline static uintptr_t jit_a;
		inline static uintptr_t os_a;

		// function initiates
		inline static lua51_call lua_call;
		inline static lua51_createtable lua_createtable;
		inline static luaL51_error luaL_error;
		inline static lua51_getfield lua_getfield;
		inline static lua51_getmetatable lua_getmetatable;
		inline static lua51_gettop lua_gettop;
		inline static lua51_iscfunction lua_iscfunction;
		inline static lua51_isnumber lua_isnumber;
		inline static lua51_isstring lua_isstring;
		inline static luaL51_loadstring luaL_loadstring;
		inline static luaL51_newmetatable lua_newmetatable;
		inline static luaL51_newstate luaL_newstate;
		inline static lua51_newthread lua_newthread;
		inline static lua51_next lua_next;
		inline static lua51_objlen lua_objlen;
		inline static lua51_pcall lua_pcall;
		inline static lua51_pushboolean lua_pushboolean;
		inline static lua51_pushcclosure lua_pushcclosure;
		inline static lua51_pushinteger lua_pushinteger;
		inline static lua51_pushnil lua_pushnil;
		inline static lua51_pushnumber lua_pushnumber;
		inline static lua51_pushstring lua_pushstring;
		inline static lua51_pushvalue lua_pushvalue;
		inline static lua51_rawgeti lua_rawgeti;
		inline static luaL51_ref luaL_ref;
		inline static luaL51_register luaL_register;
		inline static lua51_resume lua_resume;
		inline static lua51_setfield lua_setfield;
		inline static lua51_setmetatable lua_setmetatable;
		inline static lua51_settable lua_settable;
		inline static lua51_settop lua_settop;
		inline static lua51_toboolean lua_toboolean;
		inline static lua51_tocfunction lua_tocfunction;
		inline static lua51_tointeger lua_tointeger;
		inline static lua51_tolstring lua_tolstring;
		inline static lua51_tonumber lua_tonumber;
		inline static lua51_type lua_type;
		inline static luaL51_unref luaL_unref;
		inline static lua51_xmove lua_xmove;

		// library function initiates
		inline static lib51_bit luaopen_bit;
		inline static lib51_debug luaopen_debug;
		inline static lib51_ffi luaopen_ffi;
		inline static lib51_io luaopen_io;
		inline static lib51_jit luaopen_jit;
		inline static lib51_os luaopen_os;
	};

	class noita {
	public:
		// define noitas lua function library
		typedef void(__fastcall* nlib)(lua_State* L);

		// pointers to noita functions, values, etc in memory
		// found mostly with Ghidra
		inline static uintptr_t isbetabuild;
		inline static uintptr_t noitabase;
		inline static uintptr_t security_cookie;
		inline static uintptr_t seed;
		inline static uintptr_t noitalibrary_init;
		inline static uintptr_t restriction_checkifmod;
		inline static uintptr_t mapi_check;

		// noita library function initiate
		inline static nlib lib;

		// first lua_state grabbed, used for console execution and debugging
		inline static lua_State* first;

		// our hooked version of noita library function
		static void __fastcall nlib_hook(lua_State* L);
	};

	class beefcake {
	public:

		// Beefcake globals
		static int AddSpellToWand(lua_State* L);
		static int CreateWand(lua_State* L);
		static int EntityGetChild(lua_State* L);
		static int ExecuteThroughLoader(lua_State* L);
		static int ForceSeed(lua_State* L);
		static int GenomeGetHerdId(lua_State* L);
		static int Print(lua_State* L);
		static int SetWorldTime(lua_State* L);
		static int SpawnFlask(lua_State* L);
		static int SpawnPerk(lua_State* L);
		static int SpawnSpell(lua_State* L);

		// input library
		static int MouseLeftDown(lua_State* L);
		static int MouseRightDown(lua_State* L);
		//static int KeyDown(lua_State* L);

		// task library
		static int ForceIsBetaBuild(lua_State* L);
		static int GetCFunctionPointer(lua_State* L);
		static int GetState(lua_State* L);
		static int ReadMemory(lua_State* L);
		//static int Pocket(lua_State* L);


		// LocalPlayer library
		static int AddPerk(lua_State* L);
		static int GetIgnored(lua_State* L);
		static int GetPlayer(lua_State* L);
		static int GetPlayerAir(lua_State* L);
		static int GetPlayerAirM(lua_State* L);
		static int GetPlayerClimb(lua_State* L);
		static int GetPlayerGold(lua_State* L);
		static int GetPlayerHealth(lua_State* L);
		static int GetPlayerHealthM(lua_State* L);
		static int GetPlayerJetpack(lua_State* L);
		static int GetPlayerJetpackRecharge(lua_State* L);
		static int GetPlayerNeedsAir(lua_State* L);
		static int GetPlayerPos(lua_State* L);
		static int GetPlayerQInventory(lua_State* L);
		static int GetPlayerStomachSize(lua_State* L);
		static int SetIgnored(lua_State* L);
		static int SetPlayerAir(lua_State* L);
		static int SetPlayerAirM(lua_State* L);
		static int SetPlayerClimb(lua_State* L);
		static int SetPlayerGold(lua_State* L);
		static int SetPlayerHealth(lua_State* L);
		static int SetPlayerHealthM(lua_State* L);
		static int SetPlayerJetpack(lua_State* L);
		//static int SetPlayerJetpackRecharge(lua_State* L); will add eventually
		static int SetPlayerNeedsAir(lua_State* L);
		static int SetPlayerPos(lua_State* L);
		static int SetPlayerStomachSize(lua_State* L);
	};

	// init for everything
	static void luahook_init();
};
