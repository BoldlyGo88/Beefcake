#ifndef N_LUA_H
#define N_LUA_H

#include "hlua.h"

//typedef void(__fastcall* nlib)(lua_State* L);
typedef void(__fastcall* nModDevGenerateSpriteUVsForDirectory)(lua_State* L, const char* directory_path, bool override_existing);
typedef void(__fastcall* nModLuaFileAppend)(lua_State* L, const char* to_filename, const char* from_filename);
typedef void(__fastcall* nModMagicNumbersFileAdd)(lua_State* L, const char* filename);
typedef void(__fastcall* nModMaterialsFileAdd)(lua_State* L, const char* filename);
typedef void(__fastcall* nModRegisterAudioEventMappings)(lua_State* L, const char* filename);
typedef const char*(__fastcall* nModTextFileGetContent)(lua_State* L, const char* filename);
typedef const char*(__fastcall* nModTextFileWhoSetContent)(lua_State* L, const char* filename);
typedef void(__fastcall* nModTextSetFileContent)(lua_State* L, const char* filename, const char* new_content);

//extern nlib lib;
extern nModDevGenerateSpriteUVsForDirectory ModDevGenerateSpriteUVsForDirectory; // this name is outrageously long who approved this
extern nModLuaFileAppend ModLuaFileAppend;
extern nModMagicNumbersFileAdd ModMagicNumbersFileAdd;
extern nModMaterialsFileAdd ModMaterialsFileAdd;
extern nModRegisterAudioEventMappings ModRegisterAudioEventMappings;
extern nModTextFileGetContent ModTextFileGetContent;
extern nModTextFileWhoSetContent ModTextFileWhoSetContent;
extern nModTextSetFileContent ModTextSetFileContent;

extern uintptr_t noita_base;
extern lua_State* L;
extern lua_State* unsafeState;
void nlua_init();

enum nlua_offsets {
	function_library = 0x31D3E3,
	mod_api_table = 0xBF6A84,
	mod_set_one = 0x242297, 
	moddevspriteuv = 0x35A6A0,
	modluafileappend = 0x359560,
	modmagicnumbers = 0x359F90,
	modmaterials = 0x35A110,
	modregisteraudio = 0x35A290,
	modtextfilegetcontent = 0x359770,
	modtextfilewhosetcontent = 0x359CF0,
	modtextsetfilecontent = 0x359A10,
};
#endif