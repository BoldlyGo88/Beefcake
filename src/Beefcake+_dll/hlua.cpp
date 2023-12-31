#include "hlua.h"
#include <libloaderapi.h>

uintptr_t lua_base = 0;
lua_call call = NULL;
lua_createtable createtable = NULL;
luaL_error error = NULL;
lua_getfield getfield = NULL;
lua_getmetatable getmetatable = NULL;
lua_gettop gettop = NULL;
lua_iscfunction iscfunction = NULL;
lua_isnumber isnumber = NULL;
lua_isstring isstring = NULL;
luaL_loadstring loadstring = NULL;
luaL_newmetatable newmetatable = NULL;
luaL_newstate newstate = NULL;
lua_newthread newthread = NULL;
lua_next next = NULL;
lua_objlen objlen = NULL;
lua_pcall pcall = NULL;
lua_pushboolean pushboolean = NULL;
lua_pushcclosure pushcclosure = NULL;
lua_pushinteger pushinteger = NULL;
lua_pushnil pushnil = NULL;
lua_pushnumber pushnumber = NULL;
lua_pushstring pushstring = NULL;
lua_pushvalue pushvalue = NULL;
lua_rawgeti rawgeti = NULL;
luaL_ref ref = NULL;
lua_resume resume = NULL;
lua_setfield setfield = NULL;
lua_setmetatable setmetatable = NULL;
lua_settable settable = NULL;
lua_settop settop = NULL;
lua_toboolean toboolean = NULL;
lua_tocfunction tocfunction = NULL;
lua_tointeger tointeger = NULL;
lua_tolstring tolstring = NULL;
lua_tonumber tonumber = NULL;
lua_type type = NULL;
luaL_unref unref = NULL;
lua_xmove xmove = NULL;
lua_lib_standard luaopen_bit = NULL;
lua_lib_standard luaopen_debug = NULL;
lua_lib_standard luaopen_ffi = NULL;
lua_lib_standard luaopen_io = NULL;
lua_lib_standard luaopen_jit = NULL;
lua_lib_standard luaopen_os = NULL;

void hlua_init() {
	lua_base = (uintptr_t)GetModuleHandleA("lua51a.dll");
	call = (lua_call)(lua_base + lua_offsets::e_call);
	error = (luaL_error)(lua_base + lua_offsets::e_error);
	getfield = (lua_getfield)(lua_base + lua_offsets::e_getfield);
	getmetatable = (lua_getmetatable)(lua_base + lua_offsets::e_getmetatable);
	gettop = (lua_gettop)(lua_base + lua_offsets::e_gettop);
	iscfunction = (lua_iscfunction)(lua_base + lua_offsets::e_iscfunction);
	isnumber = (lua_isnumber)(lua_base + lua_offsets::e_isnumber);
	isstring = (lua_isstring)(lua_base + lua_offsets::e_isstring);
	loadstring = (luaL_loadstring)(lua_base + lua_offsets::e_loadstring);
	newmetatable = (luaL_newmetatable)(lua_base + lua_offsets::e_newmetatable);
	newstate = (luaL_newstate)(lua_base + lua_offsets::e_newstate);
	newthread = (lua_newthread)(lua_base + lua_offsets::e_newthread);
	next = (lua_next)(lua_base + lua_offsets::e_next);
	objlen = (lua_objlen)(lua_base + lua_offsets::e_objlen);
	pcall = (lua_pcall)(lua_base + lua_offsets::e_pcall);
	pushboolean = (lua_pushboolean)(lua_base + lua_offsets::e_pushboolean);
	pushcclosure = (lua_pushcclosure)(lua_base + lua_offsets::e_pushcclosure);
	pushinteger = (lua_pushinteger)(lua_base + lua_offsets::e_pushinteger);
	pushnil = (lua_pushnil)(lua_base + lua_offsets::e_pushnil);
	pushnumber = (lua_pushnumber)(lua_base + lua_offsets::e_pushnumber);
	pushstring = (lua_pushstring)(lua_base + lua_offsets::e_pushstring);
	pushvalue = (lua_pushvalue)(lua_base + lua_offsets::e_pushvalue);
	rawgeti = (lua_rawgeti)(lua_base + lua_offsets::e_rawgeti);
	ref = (luaL_ref)(lua_base + lua_offsets::e_ref);
	resume = (lua_resume)(lua_base + lua_offsets::e_resume);
	setfield = (lua_setfield)(lua_base + lua_offsets::e_setfield);
	setmetatable = (lua_setmetatable)(lua_base + lua_offsets::e_setmetatable);
	settable = (lua_settable)(lua_base + lua_offsets::e_settable);
	settop = (lua_settop)(lua_base + lua_offsets::e_settop);
	toboolean = (lua_toboolean)(lua_base + lua_offsets::e_toboolean);
	tocfunction = (lua_tocfunction)(lua_base + lua_offsets::e_tocfunction);
	tointeger = (lua_tointeger)(lua_base + lua_offsets::e_tointeger);
	tolstring = (lua_tolstring)(lua_base + lua_offsets::e_tolstring);
	tonumber = (lua_tonumber)(lua_base + lua_offsets::e_tonumber);
	type = (lua_type)(lua_base + lua_offsets::e_type);
	unref = (luaL_unref)(lua_base + lua_offsets::e_unref);
	xmove = (lua_xmove)(lua_base + lua_offsets::e_xmove);
	luaopen_bit = (lua_lib_standard)(lua_base + lua_offsets::lib_bit);
	luaopen_debug = (lua_lib_standard)(lua_base + lua_offsets::lib_debug);
	luaopen_ffi = (lua_lib_standard)(lua_base + lua_offsets::lib_ffi);
	luaopen_io = (lua_lib_standard)(lua_base + lua_offsets::lib_io);
	luaopen_jit = (lua_lib_standard)(lua_base + lua_offsets::lib_jit);
	luaopen_os = (lua_lib_standard)(lua_base + lua_offsets::lib_os);
}