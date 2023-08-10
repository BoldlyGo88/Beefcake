#ifndef BEEFCAKE_H
#define BEEFCAKE_H
#include "hlua.h"
#include <map>

// Globals
int AddSpellToWand(lua_State* L);
int CreateWand(lua_State* L);
int EditWand(lua_State* L);
int EntityGetChild(lua_State* L);
int ForceSeed(lua_State* L);
int GenomeGetHerdId(lua_State* L);
int Print(lua_State* L);
int SetWorldTime(lua_State* L);
int SpawnFlask(lua_State* L);
int SpawnPerk(lua_State* L);
int SpawnSpell(lua_State* L);

// Input Library
int KeyDown(lua_State* L);
int MouseLeftDown(lua_State* L);
int MouseRightDown(lua_State* L);

// LocalPlayer library
int AddPerk(lua_State* L);
int GetIgnored(lua_State* L);
int GetPlayer(lua_State* L);
int GetPlayerAir(lua_State* L);
int GetPlayer(lua_State* L);
int GetPlayerAir(lua_State* L);
int GetPlayerAirM(lua_State* L);
int GetPlayerClimb(lua_State* L);
int GetPlayerGold(lua_State* L);
int GetPlayerGoldSpent(lua_State* L);
int GetPlayerHealth(lua_State* L);
int GetPlayerHealthM(lua_State* L);
int GetPlayerJetpack(lua_State* L);
int GetPlayerJetpackRecharge(lua_State* L);
int GetPlayerNeedsAir(lua_State* L);
int GetPlayerPos(lua_State* L);
int GetPlayerQInventory(lua_State* L);
int GetPlayerStomachFullness(lua_State* L);
int GetPlayerStomachSize(lua_State* L);
int SetIgnored(lua_State* L);
int SetPlayerAir(lua_State* L);
int SetPlayerAirM(lua_State* L);
int SetPlayerClimb(lua_State* L);
int SetPlayerGold(lua_State* L);
int SetPlayerHealth(lua_State* L);
int SetPlayerHealthM(lua_State* L);
int SetPlayerJetpack(lua_State* L);
int SetPlayerNeedsAir(lua_State* L);
int SetPlayerPos(lua_State* L);
int SetPlayerStomachFullness(lua_State* L);
int SetPlayerStomachSize(lua_State* L);

// Task library
int ExecuteThroughLoader(lua_State* L);
int ForceIsBetaBuild(lua_State* L);
int GetCFunctionPointer(lua_State* L);
int GetState(lua_State* L);

#endif