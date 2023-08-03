#ifndef H_LUA_H
#define H_LUA_H

#include <windows.h>
#include <cstddef>

#define LUA_REGISTRYINDEX	(-10000)
#define LUA_ENVIRONINDEX	(-10001)
#define LUA_GLOBALSINDEX	(-10002)

#define LUA_OK			0
#define LUA_YIELD	1
#define LUA_ERRRUN	2
#define LUA_ERRSYNTAX	3
#define LUA_ERRMEM	4
#define LUA_ERRERR	5

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

#define nregister(L,n,f) (pushcfunction(L, (f)), setglobal(L, (n)))
#define vregister(L,t,n,v) (t(L, v), setglobal(L, n))
#define pushcfunction(L,f)	pushcclosure(L, (f), 0)
#define setglobal(L,s)	setfield(L, LUA_GLOBALSINDEX, (s))
#define getglobal(L,s)	getfield(L, LUA_GLOBALSINDEX, (s))
#define pop(L,n)		settop(L, -(n)-1)
#define newtable(L)		createtable(L, 0, 0)



typedef struct lua_State lua_State;
typedef int(__cdecl* lua_CFunction)(lua_State* L);
typedef struct luaL_Reg { const char* name; lua_CFunction func; } luaL_Reg;
typedef double lua_Number;
typedef ptrdiff_t lua_Integer;
typedef void(__cdecl* lua_call)(lua_State* L, int nargs, int nresults);
typedef void(__cdecl* lua_createtable)(lua_State* L, int narr, int nrec);
typedef int(__cdecl* luaL_error)(lua_State* L, const char* fmt, ...);
typedef void(__cdecl* lua_getfield)(lua_State* L, int idx, const char* k);
typedef int(__cdecl* lua_getmetatable)(lua_State* L, int index);
typedef int(__cdecl* lua_gettop)(lua_State* L);
typedef int(__cdecl* lua_iscfunction)(lua_State* L, int idx);
typedef int(__cdecl* lua_isnumber)(lua_State* L, int idx);
typedef int(__cdecl* lua_isstring)(lua_State* L, int idx);
typedef void(__cdecl* luaL_loadstring)(lua_State* L, const char* s);
typedef int(__cdecl* luaL_newmetatable)(lua_State* L, const char* tname);
typedef lua_State* (__cdecl* luaL_newstate)(void);
typedef lua_State* (__cdecl* lua_newthread)(lua_State* L);
typedef int(__cdecl* lua_next)(lua_State* L, int index);
typedef size_t(__cdecl* lua_objlen)(lua_State* L, int index);
typedef int(__cdecl* lua_pcall)(lua_State* L, int nargs, int nresults, int errfunc);
typedef void(__cdecl* lua_pushboolean)(lua_State* L, int b);
typedef void(__cdecl* lua_pushcclosure)(lua_State* L, lua_CFunction f, int n);
typedef void(__cdecl* lua_pushinteger)(lua_State* L, lua_Integer n);
typedef void(__cdecl* lua_pushnil)(lua_State* L);
typedef void(__cdecl* lua_pushnumber)(lua_State* L, lua_Number n);
typedef void(__cdecl* lua_pushstring)(lua_State* L, const char* str);
typedef void(__cdecl* lua_pushvalue)(lua_State* L, int idx);
typedef void(__cdecl* lua_rawgeti)(lua_State* L, int idx, int n);
typedef int(__cdecl* luaL_ref)(lua_State* L, int t);
typedef void(__cdecl* luaL_register)(lua_State* L, const char* libname, const luaL_Reg* l);
typedef int(__cdecl* lua_resume)(lua_State* L, int narg);
typedef void(__cdecl* lua_setfield)(lua_State* L, int idx, const char* k);
typedef void(__cdecl* lua_setmetatable)(lua_State* L, int index);
typedef void(__cdecl* lua_settable)(lua_State* L, int index);
typedef void(__cdecl* lua_settop)(lua_State* L, int idx);
typedef int(__cdecl* lua_toboolean)(lua_State* L, int idx);
typedef lua_CFunction(__cdecl* lua_tocfunction)(lua_State* L, int idx);
typedef lua_Integer(__cdecl* lua_tointeger)(lua_State* L, int idx);
typedef const char* (__cdecl* lua_tolstring)(lua_State* L, int idx, size_t* len);
typedef lua_Number(__cdecl* lua_tonumber)(lua_State* L, int idx);
typedef int(__cdecl* lua_type)(lua_State* L, int index);
typedef void(__cdecl* luaL_unref)(lua_State* L, int t, int ref);
typedef void(__cdecl* lua_xmove)(lua_State* from, lua_State* to, int n);

typedef void(__cdecl* lua_lib_standard)(lua_State* L);

extern lua_call call;
extern lua_createtable createtable;
extern luaL_error error;
extern lua_getfield getfield;
extern lua_getmetatable getmetatable;
extern lua_gettop gettop;
extern lua_iscfunction iscfunction;
extern lua_isnumber isnumber;
extern lua_isstring isstring;
extern luaL_loadstring loadstring;
extern luaL_newmetatable newmetatable;
extern luaL_newstate newstate;
extern lua_newthread newthread;
extern lua_next next;
extern lua_objlen objlen;
extern lua_pcall pcall;
extern lua_pushboolean pushboolean;
extern lua_pushcclosure pushcclosure;
extern lua_pushinteger pushinteger;
extern lua_pushnil pushnil;
extern lua_pushnumber pushnumber;
extern lua_pushstring pushstring;
extern lua_pushvalue pushvalue;
extern lua_rawgeti rawgeti;
extern luaL_ref ref;
extern luaL_register lregister;
extern lua_resume resume;
extern lua_setfield setfield;
extern lua_setmetatable setmetatable;
extern lua_settable settable;
extern lua_settop settop;
extern lua_toboolean toboolean;
extern lua_tocfunction tocfunction;
extern lua_tointeger tointeger;
extern lua_tolstring tolstring;
extern lua_tonumber tonumber;
extern lua_type type;
extern luaL_unref unref;
extern lua_xmove xmove;

extern lua_lib_standard luaopen_bit;
extern lua_lib_standard luaopen_debug;
extern lua_lib_standard luaopen_ffi;
extern lua_lib_standard luaopen_io;
extern lua_lib_standard luaopen_jit;
extern lua_lib_standard luaopen_os;

extern uintptr_t lua_base;

void hlua_init();

enum lua_offsets {
	e_call = 0x6870,
	e_createtable = 0x69D0,
	e_error = 0x23030,				// unused
	e_getfield = 0x6C90,
	e_getmetatable = 0x6D40,		// unused, not initialized
	e_gettop = 0x6E20,
	e_iscfunction = 0x6F00,
	e_isnumber = 0x6F30,
	e_isstring = 0x6F80,
	e_loadstring = 0x29C20,			// unused-ish
	e_newmetatable = 0x6640,
	e_newstate = 0x3E150,			// unused, not initialized
	e_newthread = 0x7070,			// unused, not initialized
	e_next = 0x7140,
	e_objlen = 0x7190,				// unused
	e_pcall = 0x71F0,
	e_pushcclosure = 0x72A0,		// unused
	e_pushboolean = 0x7270,
	e_pushinteger = 0x7360,
	e_pushnil = 0x7410,
	e_pushnumber = 0x7430,
	e_pushstring = 0x7470,
	e_pushvalue = 0x7520,
	e_rawgeti = 0x7610,
	e_ref = 0x43020,				// unused, not initialized
	e_register = 0x430D0,
	e_resume = 0x7890,				// unused
	e_setfield = 0x79A0,			// unused
	e_setmetatable = 0x7A50,
	e_settable = 0x7B80,			// unused
	e_settop = 0x7BF0,
	e_toboolean = 0x7D00,
	e_tocfunction = 0x7D20,
	e_tointeger = 0x7D50,
	e_tolstring = 0x7DB0,
	e_tonumber = 0x7E30,
	e_type = 0x7F10,
	e_unref = 0x430F0,				// unused, not initialized
	e_xmove = 0x7FF0,				// unused
	lib_bit = 0x44410,
	lib_debug = 0x45050,
	lib_ffi = 0x46A80,
	lib_io = 0x47A80,
	lib_jit = 0x48C10,
	lib_os = 0x49980
};
#endif