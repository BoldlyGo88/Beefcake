#ifndef N_LUA_H
#define N_LUA_H

#include "hlua.h"


typedef void(__fastcall* nlib)(lua_State* L);
typedef void(__fastcall* nModDevGenerateSpriteUVsForDirectory)(lua_State* L, const char* directory_path, bool override_existing);
typedef void(__fastcall* nModLuaFileAppend)(lua_State* L, const char* to_filename, const char* from_filename);
typedef void(__fastcall* nModMagicNumbersFileAdd)(lua_State* L, const char* filename);
typedef void(__fastcall* nModMaterialsFileAdd)(lua_State* L, const char* filename);
typedef void(__fastcall* nModRegisterAudioEventMappings)(lua_State* L, const char* filename);
typedef const char*(__fastcall* nModTextFileGetContent)(lua_State* L, const char* filename);
typedef const char*(__fastcall* nModTextFileWhoSetContent)(lua_State* L, const char* filename);
typedef void(__fastcall* nModTextSetFileContent)(lua_State* L, const char* filename, const char* new_content);

extern nlib lib;
extern nModDevGenerateSpriteUVsForDirectory ModDevGenerateSpriteUVsForDirectory; // this name is outrageously long who approved this
extern nModLuaFileAppend ModLuaFileAppend;
extern nModMagicNumbersFileAdd ModMagicNumbersFileAdd;
extern nModMaterialsFileAdd ModMaterialsFileAdd;
extern nModRegisterAudioEventMappings ModRegisterAudioEventMappings;
extern nModTextFileGetContent ModTextFileGetContent;
extern nModTextFileWhoSetContent ModTextFileWhoSetContent;
extern nModTextSetFileContent ModTextSetFileContent;

extern uintptr_t noita_base;
extern lua_State* state;
extern lua_State* unsafeState;

void nlua_init();
void __fastcall nlib_hook(lua_State* L);
void writeINT(uintptr_t address, int value);

enum nlua_offsets {
	function_library = 0x31BF20,
	isbetabuild = 0xB41074,
	mod_api_table = 0xBF5A54,
	mod_ismodding = 0x00000120,
	mod_set_ismodding = 0x2429DB,
	moddevspriteuv = 0x35AF90,
	modluafileappend = 0x359E50,
	modmagicnumbers = 0x35A880,
	modmaterials = 0x35AA00,
	modregisteraudio = 0x35AB80,
	modtextfilegetcontent = 0x35A060,
	modtextfilewhosetcontent = 0x35A5E0,
	modtextsetfilecontent = 0x35A300,
	world_seed = 0xBF5A48
};
#endif