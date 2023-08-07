#include "beefcake.h"
#include "nlua.h"
#include <string>
#include <iostream>

// Globals
int AddSpellToWand(lua_State* L) {
	if (gettop(L) != 3 || type(L, 1) != LUA_TNUMBER && type(L, 2) != LUA_TSTRING && type(L, 3) != LUA_TNUMBER)
		return error(L, "Argument Error: %s", tolstring(L, -1, NULL));

	int wand = tointeger(L, 1);
	const char* spell = tolstring(L, 2, NULL);
	int perm = toboolean(L, 3);
	if (spell == "")
		return error(L, "Spell Argument Error: %s", tolstring(L, -2, NULL));
	getglobal(L, "CreateItemActionEntity");
	pushstring(L, spell);
	pushnumber(L, 0);
	pushnumber(L, 0);
	if (pcall(L, 3, 1, 0) != 0)
		return error(L, "CreateItemActionEntity Error: %s", tolstring(L, -1, NULL));
	int action = tointeger(L, -1);
	pop(L, 1);
	if (action != 0)
	{
		if (perm == 0)
		{
			getglobal(L, "EntityAddChild");
			pushinteger(L, wand);
			pushinteger(L, action);
			if (pcall(L, 2, 0, 0) != 0)
				return error(L, "EntityAddChild Error: %s", tolstring(L, -1, NULL));
			getglobal(L, "EntitySetComponentsWithTagEnabled");
			pushinteger(L, action);
			pushstring(L, "enabled_in_world");
			pushboolean(L, 0);
			if (pcall(L, 3, 0, 0) != 0)
				return error(L, "EntitySetComponentsWithTagEnabled Error: %s", tolstring(L, -1, NULL));
			return 0;
		}
		else {
			getglobal(L, "EntityGetFirstComponentIncludingDisabled");
			pushinteger(L, wand);
			pushstring(L, "AbilityComponent");
			if (pcall(L, 2, 1, 0) != 0)
				return error(L, "EntityGetFirstComponentIncludingDisabled Error: %s", tolstring(L, -1, NULL));
			int ac = tointeger(L, -1);
			pop(L, 1);
			getglobal(L, "ComponentObjectGetValue2");
			pushinteger(L, ac);
			pushstring(L, "gun_config");
			pushstring(L, "deck_capacity");
			if (pcall(L, 3, 1, 0) != 0)
				return error(L, "ComponentObjectGetValue2 Error: %s", tolstring(L, -1, NULL));
			int cap = (int)tonumber(L, -1);
			pop(L, 1);
			getglobal(L, "ComponentObjectSetValue2");
			pushinteger(L, ac);
			pushstring(L, "gun_config");
			pushstring(L, "deck_capacity");
			pushinteger(L, cap + 1);
			if (pcall(L, 4, 0, 0) != 0)
				return error(L, "ComponentObjectSetValue2 Error: %s", tolstring(L, -1, NULL));
			getglobal(L, "EntityGetFirstComponent");
			pushinteger(L, action);
			pushstring(L, "ItemComponent");
			if (pcall(L, 2, 1, 0) != 0)
				return error(L, "EntityGetFirstComponent Error: %s", tolstring(L, -1, NULL));
			int ic = tointeger(L, -1);
			pop(L, 1);
			getglobal(L, "ComponentSetValue2");
			pushinteger(L, ic);
			pushstring(L, "permanently_attached");
			pushboolean(L, 1);
			if (pcall(L, 3, 0, 0) != 0)
				return error(L, "ComponentSetValue2 Error: %s", tolstring(L, -1, NULL));
			getglobal(L, "EntityAddChild");
			pushinteger(L, wand);
			pushinteger(L, action);
			if (pcall(L, 2, 0, 0) != 0)
				return error(L, "EntityAddChild Error: %s", tolstring(L, -1, NULL));
			getglobal(L, "EntitySetComponentsWithTagEnabled");
			pushinteger(L, action);
			pushstring(L, "enabled_in_world");
			pushboolean(L, 0);
			if (pcall(L, 3, 0, 0) != 0)
				return error(L, "EntitySetComponentsWithTagEnabled Error: %s", tolstring(L, -1, NULL));
		}
	}
	return 0;
}

int CreateWand(lua_State* L) {
	if (unsafeState == L) {
		std::cout << "\x1B[31m" << "This function is restricted from being executed through the Beefcake Console. Use task.ExecuteTL() to get around this." << "\033[0m" << std::endl;
		return 0;
	}

	if (gettop(L) != 10 || type(L, 1) != LUA_TSTRING && type(L, 2) != LUA_TNUMBER && type(L, 3) != LUA_TNUMBER && type(L, 4) != LUA_TNUMBER
		&& type(L, 5) != LUA_TNUMBER && type(L, 6) != LUA_TNUMBER && type(L, 7) != LUA_TNUMBER && type(L, 8) != LUA_TSTRING
		&& type(L, 9) != LUA_TNUMBER && type(L, 10) != LUA_TNUMBER)
		return error(L, "Argument Error: %s", tolstring(L, -1, NULL));

	const char* name = tolstring(L, 1, NULL);
	double mana_charge = tonumber(L, 2);
	double mana_max = tonumber(L, 3);
	double reloadspeed = tonumber(L, 4);
	double recoil = tonumber(L, 5);
	int actions_per_round = (int)tonumber(L, 6);
	int capacity = (int)tonumber(L, 7);
	const char* entity = tolstring(L, 8, NULL);
	int entity_offset_x = tointeger(L, 9);
	int entity_offset_y = tointeger(L, 10);
	if (mana_charge <= 0)
		mana_charge = 100;
	if (mana_max <= 0)
		mana_max = 75;
	getglobal(L, "EntityGetWithTag");
	pushstring(L, "player_unit");
	if (pcall(L, 1, 1, 0) != 0)
		return error(L, "EntityGetWithTag Error: %s", tolstring(L, -1, NULL));
	rawgeti(L, -1, 1);
	int player = tointeger(L, -1);
	getglobal(L, "EntityGetTransform");
	pushinteger(L, player);
	if (pcall(L, 1, 2, 0) != 0)
		return error(L, "EntityGetTransform Error: %s", tolstring(L, -1, NULL));
	double x = tonumber(L, -1);
	double y = tonumber(L, -2);
	pop(L, 2);
	getglobal(L, "EntityLoad");
	pushstring(L, "data/entities/items/starting_wand.xml");
	pushnumber(L, y);
	pushnumber(L, x);
	if (pcall(L, 3, 1, 0) != 0)
		return error(L, "EntityLoad Error: %s", tolstring(L, -1, NULL));
	int wand = tointeger(L, -1);
	pop(L, 1);
	getglobal(L, "EntityGetFirstComponent");
	pushinteger(L, wand);
	pushstring(L, "AbilityComponent");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "EntityGetFirstComponent Error: %s", tolstring(L, -1, NULL));
	int ac = tointeger(L, -1);
	pop(L, 1);
	getglobal(L, "EntityGetFirstComponent");
	pushinteger(L, wand);
	pushstring(L, "SpriteComponent");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "EntityGetFirstComponent Error: %s", tolstring(L, -1, NULL));
	int sc = tointeger(L, -1);
	pop(L, 1);
	getglobal(L, "EntityRemoveFromParent");
	pushinteger(L, wand + 1);
	if (pcall(L, 1, 0, 0) != 0)
		return error(L, "EntityRemoveFromParent Error: %s", tolstring(L, -1, NULL));
	getglobal(L, "EntityRemoveFromParent");
	pushinteger(L, wand + 2);
	if (pcall(L, 1, 0, 0) != 0)
		return error(L, "EntityRemoveFromParent Error: %s", tolstring(L, -1, NULL));
	getglobal(L, "ComponentSetValue2");
	pushinteger(L, ac);
	pushstring(L, "sprite_file");
	pushstring(L, entity);
	if (pcall(L, 3, 0, 0) != 0)
		return error(L, "ComponentSetValue2 Error: %s", tolstring(L, -1, NULL));
	getglobal(L, "ComponentSetValue2");
	pushinteger(L, sc);
	pushstring(L, "image_file");
	pushstring(L, entity);
	if (pcall(L, 3, 0, 0) != 0)
		return error(L, "ComponentSetValue2 Error: %s", tolstring(L, -1, NULL));
	getglobal(L, "ComponentSetValue2");
	pushinteger(L, sc);
	pushstring(L, "offset_x");
	pushinteger(L, entity_offset_y);
	if (pcall(L, 3, 0, 0) != 0)
		return error(L, "ComponentSetValue2 Error: %s", tolstring(L, -1, NULL));
	getglobal(L, "ComponentSetValue2");
	pushinteger(L, sc);
	pushstring(L, "offset_y");
	pushinteger(L, entity_offset_x);
	if (pcall(L, 3, 0, 0) != 0)
		return error(L, "ComponentSetValue2 Error: %s", tolstring(L, -1, NULL));
	getglobal(L, "ComponentSetValue2");
	pushinteger(L, ac);
	pushstring(L, "mana_charge_speed");
	pushnumber(L, mana_charge);
	if (pcall(L, 3, 0, 0) != 0)
		return error(L, "ComponentSetValue2 Error: %s", tolstring(L, -1, NULL));
	getglobal(L, "ComponentSetValue2");
	pushinteger(L, ac);
	pushstring(L, "mana_max");
	pushnumber(L, mana_max);
	if (pcall(L, 3, 0, 0) != 0)
		return error(L, "ComponentSetValue2 Error: %s", tolstring(L, -1, NULL));
	getglobal(L, "ComponentSetValue2");
	pushinteger(L, ac);
	pushstring(L, "reload_time_frames");
	pushnumber(L, reloadspeed);
	if (pcall(L, 3, 0, 0) != 0)
		return error(L, "ComponentSetValue2 Error: %s", tolstring(L, -1, NULL));
	getglobal(L, "ComponentSetValue2");
	pushinteger(L, ac);
	pushstring(L, "item_recoil_max");
	pushnumber(L, recoil);
	if (pcall(L, 3, 0, 0) != 0)
		return error(L, "ComponentSetValue2 Error: %s", tolstring(L, -1, NULL));
	getglobal(L, "ComponentSetValue2");
	pushinteger(L, ac);
	pushstring(L, "ui_name");
	pushstring(L, name);
	if (pcall(L, 3, 0, 0) != 0)
		return error(L, "ComponentSetValue2 Error: %s", tolstring(L, -1, NULL));
	getglobal(L, "ComponentObjectSetValue2");
	pushinteger(L, ac);
	pushstring(L, "gun_config");
	pushstring(L, "actions_per_round");
	pushinteger(L, actions_per_round);
	if (pcall(L, 4, 0, 0) != 0)
		return error(L, "ComponentObjectSetValue2 Error: %s", tolstring(L, -1, NULL));
	getglobal(L, "ComponentObjectSetValue2");
	pushinteger(L, ac);
	pushstring(L, "gun_config");
	pushstring(L, "reload_time");
	pushnumber(L, reloadspeed);
	if (pcall(L, 4, 0, 0) != 0)
		return error(L, "ComponentObjectSetValue2 Error: %s", tolstring(L, -1, NULL));
	getglobal(L, "ComponentObjectSetValue2");
	pushinteger(L, ac);
	pushstring(L, "gun_config");
	pushstring(L, "deck_capacity");
	pushinteger(L, capacity);
	if (pcall(L, 4, 0, 0) != 0)
		return error(L, "ComponentObjectSetValue2 Error: %s", tolstring(L, -1, NULL));
	getglobal(L, "ComponentObjectSetValue2");
	pushinteger(L, ac);
	pushstring(L, "gun_config");
	pushstring(L, "fire_rate_wait");
	pushinteger(L, reloadspeed);
	if (pcall(L, 4, 0, 0) != 0)
		return error(L, "ComponentObjectSetValue2 Error: %s", tolstring(L, -1, NULL));
	pushinteger(L, wand);
	return 1;
}

int EntityGetChild(lua_State* L) {
	int top = gettop(L);

	if (gettop(L) != 2 || type(L, 1) != LUA_TNUMBER && type(L, 2) != LUA_TSTRING)
		return error(L, "Argument Error: %s", tolstring(L, -1, NULL));

	int entity = tointeger(L, 1);
	const char* entity2find = tolstring(L, 2, NULL);
	getglobal(L, "EntityGetAllChildren");
	pushinteger(L, entity);
	if (pcall(L, 1, 1, 0) != 0)
		return error(L, "EntityGetAllChildren Error: %s", tolstring(L, -1, NULL));

	pushnil(L);
	while (next(L, -2) != 0)
	{
		if (type(L, -2) != LUA_TNIL)
		{
			int child = tointeger(L, -1);
			getglobal(L, "EntityGetName");
			pushinteger(L, child);
			if (pcall(L, 1, 1, 0) != 0)
				return error(L, "EntityGetName Error: %s", tolstring(L, -1, NULL));

			if (isstring(L, -1))
			{
				const char* child_name = tolstring(L, -1, NULL);
				if (strcmp(child_name, entity2find) == 0)
				{
					return 2;
				}
			}
			pop(L, 1);
		}
		pop(L, 1);
	}

	settop(L, top);
	pushnil(L);
	return 1;
}

int ForceSeed(lua_State* L) {
	if (gettop(L) != 1 || type(L, 1) != LUA_TNUMBER)
		return error(L, "Argument Error: %s", tolstring(L, -1, NULL));

	int seed = tointeger(L, 1);
	writeINT(noita_base + nlua_offsets::world_seed, seed);
	return 0;
}

int GenomeGetHerdId(lua_State* L) {
	if (gettop(L) != 1 || type(L, 1) != LUA_TNUMBER)
		return error(L, "Argument Error: %s", tolstring(L, -1, NULL));

	int entity = tointeger(L, 1);
	getglobal(L, "EntityGetFirstComponent");
	pushinteger(L, entity);
	pushstring(L, "GenomeDataComponent");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "EntityGetFirstComponent Error: %s", tolstring(L, -1, NULL));
	int gdc = tointeger(L, -1);
	pop(L, 1);
	getglobal(L, "ComponentGetValue2");
	pushinteger(L, gdc);
	pushstring(L, "herd_id");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "ComponentGetValue2 Error: %s", tolstring(L, -1, NULL));
	int id = tointeger(L, -1);
	pop(L, 1);
	getglobal(L, "HerdIdToString");
	pushinteger(L, id);
	if (pcall(L, 1, 1, 0) != 0)
		return error(L, "HerdIdToString Error: %s", tolstring(L, -1, NULL));
	const char* herd_id = tolstring(L, -1, NULL);
	pop(L, 1);
	pushstring(L, herd_id);
	return 1;
}

int Print(lua_State* L) {
	int top = gettop(L);

	getglobal(L, "tostring");

	for (int x = 1; x <= top; x++){
		pushvalue(L, top + 1);
		pushvalue(L, x);
		call(L, 1, 1);

		if(!isstring(L, -1))
			return error(L, "String Conversion Error: %s", tolstring(L, -1, NULL));

		const char* str = tolstring(L, -1, NULL);
		if (str != nullptr)
			std::cout << "\x1B[32m" << "[SCRIPT]\033[0m " << str << std::endl;
	}

	return 0;
}

int SetWorldTime(lua_State* L) {
	if (gettop(L) != 1 || type(L, 1) != LUA_TNUMBER)
		return error(L, "Argument Error: %s", tolstring(L, -1, NULL));

	double time = tonumber(L, 1);
	getglobal(L, "GameGetWorldStateEntity");
	call(L, 0, 1); // todo: fix
	int world = tointeger(L, -1);
	pop(L, 1);
	getglobal(L, "EntityGetFirstComponent");
	pushinteger(L, world);
	pushstring(L, "WorldStateComponent");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "EntityGetFirstComponent Error: %s", tolstring(L, -1, NULL));
	int comp = tointeger(L, -1);
	pop(L, 1);
	getglobal(L, "ComponentSetValue2");
	pushinteger(L, comp);
	pushstring(L, "time");
	pushnumber(L, time);
	if (pcall(L, 3, 1, 0) != 0)
		return error(L, "ComponentSetValue2 Error: %s", tolstring(L, -1, NULL));
	settop(L, 0);
	return 0;
}

int SpawnFlask(lua_State* L) {
	if (gettop(L) != 4 || type(L, 1) != LUA_TSTRING && type(L, 2) != LUA_TNUMBER && type(L, 3) != LUA_TNUMBER && type(L, 4) != LUA_TNUMBER)
		return error(L, "Argument Error: %s", tolstring(L, -1, NULL));

	const char* flask = tolstring(L, 1, NULL);
	double x = tonumber(L, 2);
	double y = tonumber(L, 3);
	double amount = tonumber(L, 4);
	getglobal(L, "EntityLoad");
	pushstring(L, "data/entities/items/pickup/potion_empty.xml");
	pushnumber(L, x);
	pushnumber(L, y);
	if (pcall(L, 3, 1, 0) != 0)
		return error(L, "EntityLoad Error: %s", tolstring(L, -1, NULL));
	int pot = tointeger(L, -1);
	pop(L, 1);
	getglobal(L, "AddMaterialInventoryMaterial");
	pushinteger(L, pot);
	pushstring(L, flask);
	pushnumber(L, amount);
	if (pcall(L, 3, 0, 0) != 0)
		return error(L, "AddMaterialInventoryMaterial Error: %s", tolstring(L, -1, NULL));
	settop(L, 0);
	return 0;
}

int SpawnPerk(lua_State* L) {
	if (unsafeState == L) {
		std::cout << "\x1B[31m" << "This function is restricted from being executed through the Beefcake Console. Use task.ExecuteTL() to get around this." << "\033[0m" << std::endl;
		return 0;
	}

	if (gettop(L) != 3 || type(L, 1) != LUA_TSTRING && type(L, 2) != LUA_TNUMBER && type(L, 3) != LUA_TNUMBER)
		return error(L, "Argument Error: %s", tolstring(L, -1, NULL));

	const char* perk = tolstring(L, 1, NULL);
	double x = tonumber(L, 2);
	double y = tonumber(L, 3);
	getglobal(L, "dofile_once");
	pushstring(L, "data/scripts/perks/perk.lua");
	if (pcall(L, 1, 1, 0) != 0)
		return error(L, "dofile_once Error: %s", tolstring(L, -1, NULL));
	getglobal(L, "perk_spawn");
	pushnumber(L, x);
	pushnumber(L, y);
	pushstring(L, perk);
	if (pcall(L, 3, 1, 0) != 0)
		return error(L, "perk_spawn Error: %s", tolstring(L, -1, NULL));
	//settop(L, 0);
	return 0;
}

int SpawnSpell(lua_State* L) {
	if (unsafeState == L) {
		std::cout << "\x1B[31m" << "This function is restricted from being executed through the Beefcake Console. Use task.ExecuteTL() to get around this." << "\033[0m" << std::endl;
		return 0;
	}

	if (gettop(L) != 3 || type(L, 1) != LUA_TSTRING && type(L, 2) != LUA_TNUMBER && type(L, 3) != LUA_TNUMBER)
		return error(L, "Argument Error: %s", tolstring(L, -1, NULL));

	const char* spell = tolstring(L, 1, NULL);
	double x = tonumber(L, 2);
	double y = tonumber(L, 3);
	getglobal(L, "CreateItemActionEntity");
	pushstring(L, spell);
	pushnumber(L, x);
	pushnumber(L, y);
	if (pcall(L, 3, 1, 0) != 0)
		return error(L, "CreateItemActionEntity Error: %s", tolstring(L, -1, NULL));
	//settop(L, 0);
	return 0;
}

// Input library
int KeyDown(lua_State* L) {
	if (gettop(L) != 1 || type(L, 1) != LUA_TSTRING)
		return error(L, "Argument Error: %s", tolstring(L, -1, NULL));

	const char* key = tolstring(L, 1, NULL);
	char realKey = key[0];

	if (GetKeyState(MapVirtualKey(realKey, MAPVK_VK_TO_CHAR)) & 0x8000) {
		pushboolean(L, true);
		return 1;
	}

	return 0;
}

int MouseLeftDown(lua_State* L) {
	getglobal(L, "EntityGetWithTag");
	pushstring(L, "player_unit");
	if (pcall(L, 1, 1, 0) != 0)
		return error(L, "EntityGetWithTag Error: %s", tolstring(L, -1, NULL));
	rawgeti(L, -1, 1);
	int player = tointeger(L, -1);
	getglobal(L, "EntityGetFirstComponent");
	pushinteger(L, player);
	pushstring(L, "ControlsComponent");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "EntityGetFirstComponent Error: %s", tolstring(L, -1, NULL));
	int concomp = tointeger(L, -1);
	pop(L, 1);
	getglobal(L, "ComponentGetValue2");
	pushinteger(L, concomp);
	pushstring(L, "mButtonDownFire2");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "ComponentGetValue2 Error: %s", tolstring(L, -1, NULL));
	return 1;
}

int MouseRightDown(lua_State* L) {
	getglobal(L, "EntityGetWithTag");
	pushstring(L, "player_unit");
	if (pcall(L, 1, 1, 0) != 0)
		return error(L, "EntityGetWithTag Error: %s", tolstring(L, -1, NULL));
	rawgeti(L, -1, 1);
	int player = tointeger(L, -1);
	getglobal(L, "EntityGetFirstComponent");
	pushinteger(L, player);
	pushstring(L, "ControlsComponent");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "EntityGetFirstComponent Error: %s", tolstring(L, -1, NULL));
	int concomp = tointeger(L, -1);
	pop(L, 1);
	getglobal(L, "ComponentGetValue2");
	pushinteger(L, concomp);
	pushstring(L, "mButtonDownThrow");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "ComponentGetValue2 Error: %s", tolstring(L, -1, NULL));
	return 1;
}


// LocalPlayer library
int AddPerk(lua_State* L) {
	if (unsafeState == L) {
		std::cout << "\x1B[31m" << "This function is restricted from being executed through the Beefcake Console. Use task.ExecuteTL() to get around this." << "\033[0m" << std::endl;
		return 0;
	}

	if (gettop(L) != 1 || type(L, 1) != LUA_TSTRING)
		return error(L, "Argument Error: %s", tolstring(L, -1, NULL));

	const char* perk = tolstring(L, 1, NULL);
	getglobal(L, "EntityGetWithTag");
	pushstring(L, "player_unit");
	if (pcall(L, 1, 1, 0) != 0)
		return error(L, "EntityGetWithTag Error: %s", tolstring(L, -1, NULL));
	rawgeti(L, -1, 1);
	int player = tointeger(L, -1);
	getglobal(L, "dofile_once");
	pushstring(L, "data/scripts/perks/perk.lua");
	if (pcall(L, 1, 1, 0) != 0)
		return error(L, "dofile_once Error: %s", tolstring(L, -1, NULL));
	getglobal(L, "perk_spawn");
	pushnumber(L, 0);
	pushnumber(L, 0);
	pushstring(L, perk);
	if (pcall(L, 3, 1, 0) != 0)
		return error(L, "perk_spawn Error: %s", tolstring(L, -1, NULL));
	int perka = tointeger(L, -1);
	pop(L, 1);
	getglobal(L, "perk_pickup");
	pushinteger(L, perka);
	pushinteger(L, player);
	pushinteger(L, 0);
	pushboolean(L, 1);
	pushboolean(L, 0);
	if (pcall(L, 5, 0, 0) != 0)
		return error(L, "perk_pickup Error: %s", tolstring(L, -1, NULL));
	settop(L, 0);
	return 0;
}

int GetIgnored(lua_State* L) {
	getglobal(L, "EntityGetWithTag");
	pushstring(L, "player_unit");
	if (pcall(L, 1, 1, 0) != 0)
		return error(L, "EntityGetWithTag Error: %s", tolstring(L, -1, NULL));
	rawgeti(L, -1, 1);
	int player = tointeger(L, -1);
	getglobal(L, "EntityGetFirstComponent");
	pushinteger(L, player);
	pushstring(L, "GenomeDataComponent");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "EntityGetFirstComponent Error: %s", tolstring(L, -1, NULL));
	int gdc = tointeger(L, -1);
	pop(L, 1);
	getglobal(L, "ComponentGetValue2");
	pushinteger(L, gdc);
	pushstring(L, "herd_id");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "ComponentGetValue2 Error: %s", tolstring(L, -1, NULL));
	const char* herd_id = tolstring(L, -1, NULL);
	pop(L, 1);
	if (strcmp(herd_id, "healer"))
	{
		pushboolean(L, 1);
		return 1;
	}
	else if (strcmp(herd_id, "player")) {
		pushboolean(L, 0);
		return 1;
	}
	else {
		return error(L, "Invalid Herd ID Gathered: ", herd_id);
	}
}

int GetPlayer(lua_State* L) {
	getglobal(L, "EntityGetWithTag");
	pushstring(L, "player_unit");
	if (pcall(L, 1, 1, 0) != LUA_OK)
		return error(L, "EntityGetWithTag Error: %s", tolstring(L, -1, NULL));
	rawgeti(L, -1, 1);
	return 1;
}

int GetPlayerAir(lua_State* L) {
	getglobal(L, "EntityGetWithTag");
	pushstring(L, "player_unit");
	if (pcall(L, 1, 1, 0) != 0)
		return error(L, "EntityGetWithTag Error: %s", tolstring(L, -1, NULL));
	rawgeti(L, -1, 1);
	int player = tointeger(L, -1);
	getglobal(L, "EntityGetFirstComponent");
	pushinteger(L, player);
	pushstring(L, "DamageModelComponent");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "EntityGetFirstComponent Error: %s", tolstring(L, -1, NULL));
	int damage = tointeger(L, -1);
	pop(L, 1);
	getglobal(L, "ComponentGetValue2");
	pushinteger(L, damage);
	pushstring(L, "air_in_lungs");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "ComponentGetValue2 Error: %s", tolstring(L, -1, NULL));
	float air = (float)tonumber(L, -1);
	pop(L, 1);
	pushnumber(L, air);
	return 1;
}

int GetPlayerAirM(lua_State* L) {
	getglobal(L, "EntityGetWithTag");
	pushstring(L, "player_unit");
	if (pcall(L, 1, 1, 0) != 0)
		return error(L, "EntityGetWithTag Error: %s", tolstring(L, -1, NULL));
	rawgeti(L, -1, 1);
	int player = tointeger(L, -1);
	getglobal(L, "EntityGetFirstComponent");
	pushinteger(L, player);
	pushstring(L, "DamageModelComponent");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "EntityGetFirstComponent Error: %s", tolstring(L, -1, NULL));
	int damage = tointeger(L, -1);
	pop(L, 1);
	getglobal(L, "ComponentGetValue2");
	pushinteger(L, damage);
	pushstring(L, "air_in_lungs_max");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "ComponentGetValue2 Error: %s", tolstring(L, -1, NULL));
	float air = (float)tonumber(L, -1);
	pop(L, 1);
	pushnumber(L, air);
	return 1;
}


int GetPlayerClimb(lua_State* L) {
	getglobal(L, "EntityGetWithTag");
	pushstring(L, "player_unit");
	if (pcall(L, 1, 1, 0) != 0)
		return error(L, "EntityGetWithTag Error: %s", tolstring(L, -1, NULL));
	rawgeti(L, -1, 1);
	int player = tointeger(L, -1);
	getglobal(L, "EntityGetFirstComponent");
	pushinteger(L, player);
	pushstring(L, "CharacterDataComponent");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "EntityGetFirstComponent Error: %s", tolstring(L, -1, NULL));
	int cdc = tointeger(L, -1);
	pop(L, 1);
	getglobal(L, "ComponentGetValue2");
	pushinteger(L, cdc);
	pushstring(L, "climb_over_y");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "ComponentGetValue2 Error: %s", tolstring(L, -1, NULL));
	int climb = tointeger(L, -1);
	pop(L, 1);
	pushinteger(L, climb);
	return 1;
}

int GetPlayerGold(lua_State* L) {
	getglobal(L, "EntityGetWithTag");
	pushstring(L, "player_unit");
	if (pcall(L, 1, 1, 0) != 0)
		return error(L, "EntityGetWithTag Error: %s", tolstring(L, -1, NULL));
	rawgeti(L, -1, 1);
	int player = tointeger(L, -1);
	getglobal(L, "EntityGetFirstComponent");
	pushinteger(L, player);
	pushstring(L, "WalletComponent");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "EntityGetFirstComponent Error: %s", tolstring(L, -1, NULL));
	int wallet = tointeger(L, -1);
	pop(L, 1);
	getglobal(L, "ComponentGetValue2");
	pushinteger(L, wallet);
	pushstring(L, "money");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "ComponentGetValue2 Error: %s", tolstring(L, -1, NULL));
	return 1;
}

int GetPlayerGoldSpent(lua_State* L) {
	getglobal(L, "EntityGetWithTag");
	pushstring(L, "player_unit");
	if (pcall(L, 1, 1, 0) != 0)
		return error(L, "EntityGetWithTag Error: %s", tolstring(L, -1, NULL));
	rawgeti(L, -1, 1);
	int player = tointeger(L, -1);
	getglobal(L, "EntityGetFirstComponent");
	pushinteger(L, player);
	pushstring(L, "WalletComponent");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "EntityGetFirstComponent Error: %s", tolstring(L, -1, NULL));
	int wallet = tointeger(L, -1);
	pop(L, 1);
	getglobal(L, "ComponentGetValue2");
	pushinteger(L, wallet);
	pushstring(L, "money_spent");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "ComponentGetValue2 Error: %s", tolstring(L, -1, NULL));
	return 1;
}

int GetPlayerHealth(lua_State* L) {
	getglobal(L, "EntityGetWithTag");
	pushstring(L, "player_unit");
	if (pcall(L, 1, 1, 0) != 0)
		return error(L, "EntityGetWithTag Error: %s", tolstring(L, -1, NULL));
	rawgeti(L, -1, 1);
	int player = tointeger(L, -1);
	getglobal(L, "EntityGetFirstComponent");
	pushinteger(L, player);
	pushstring(L, "DamageModelComponent");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "EntityGetFirstComponent Error: %s", tolstring(L, -1, NULL));
	int damage = (int)tonumber(L, -1);
	pop(L, 1);
	getglobal(L, "ComponentGetValue2");
	pushinteger(L, damage);
	pushstring(L, "hp");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "ComponentGetValue2 Error: %s", tolstring(L, -1, NULL));
	int health = (int)tonumber(L, -1);
	pop(L, 1);
	health = health * 25;
	pushinteger(L, health);
	return 1;
}

int GetPlayerHealthM(lua_State* L) {
	getglobal(L, "EntityGetWithTag");
	pushstring(L, "player_unit");
	if (pcall(L, 1, 1, 0) != 0)
		return error(L, "EntityGetWithTag Error: %s", tolstring(L, -1, NULL));
	rawgeti(L, -1, 1);
	int player = tointeger(L, -1);
	getglobal(L, "EntityGetFirstComponent");
	pushinteger(L, player);
	pushstring(L, "DamageModelComponent");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "EntityGetFirstComponent Error: %s", tolstring(L, -1, NULL));
	int damage = (int)tonumber(L, -1);
	pop(L, 1);
	getglobal(L, "ComponentGetValue2");
	pushinteger(L, damage);
	pushstring(L, "max_hp");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "ComponentGetValue2 Error: %s", tolstring(L, -1, NULL));
	int health = (int)tonumber(L, -1);
	pop(L, 1);
	health = health * 25;
	pushinteger(L, health);
	return 1;
}

int GetPlayerJetpack(lua_State* L) {
	getglobal(L, "EntityGetWithTag");
	pushstring(L, "player_unit");
	if (pcall(L, 1, 1, 0) != 0)
		return error(L, "EntityGetWithTag Error: %s", tolstring(L, -1, NULL));
	rawgeti(L, -1, 1);
	int player = tointeger(L, -1);
	getglobal(L, "EntityGetFirstComponent");
	pushinteger(L, player);
	pushstring(L, "CharacterDataComponent");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "EntityGetFirstComponent Error: %s", tolstring(L, -1, NULL));
	int cdc = tointeger(L, -1);
	pop(L, 1);
	getglobal(L, "ComponentGetValue2");
	pushinteger(L, cdc);
	pushstring(L, "fly_time_max");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "ComponentGetValue2 Error: %s", tolstring(L, -1, NULL));
	float fly = (float)tonumber(L, -1);
	pop(L, 1);
	pushnumber(L, fly);
	return 1;
}

int GetPlayerJetpackRecharge(lua_State* L) {
	getglobal(L, "EntityGetWithTag");
	pushstring(L, "player_unit");
	if (pcall(L, 1, 1, 0) != 0)
		return error(L, "EntityGetWithTag Error: %s", tolstring(L, -1, NULL));
	rawgeti(L, -1, 1);
	int player = tointeger(L, -1);
	getglobal(L, "EntityGetFirstComponent");
	pushinteger(L, player);
	pushstring(L, "CharacterDataComponent");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "EntityGetFirstComponent Error: %s", tolstring(L, -1, NULL));
	int cdc = tointeger(L, -1);
	pop(L, 1);
	getglobal(L, "ComponentGetValue2");
	pushinteger(L, cdc);
	pushstring(L, "fly_recharge_spd");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "ComponentGetValue2 Error: %s", tolstring(L, -1, NULL));
	float flyrair = (float)tonumber(L, -1);
	pop(L, 1);
	getglobal(L, "ComponentGetValue2");
	pushinteger(L, cdc);
	pushstring(L, "fly_recharge_spd_ground");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "ComponentGetValue2 Error: %s", tolstring(L, -1, NULL));
	float flyrground = (float)tonumber(L, -1);
	pop(L, 1);
	pushnumber(L, flyrair);
	pushnumber(L, flyrground);
	return 2;
}

int GetPlayerNeedsAir(lua_State* L) {
	getglobal(L, "EntityGetWithTag");
	pushstring(L, "player_unit");
	if (pcall(L, 1, 1, 0) != 0)
		return error(L, "EntityGetWithTag Error: %s", tolstring(L, -1, NULL));
	rawgeti(L, -1, 1);
	int player = tointeger(L, -1);
	getglobal(L, "EntityGetFirstComponent");
	pushinteger(L, player);
	pushstring(L, "DamageModelComponent");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "EntityGetFirstComponent Error: %s", tolstring(L, -1, NULL));
	int damage = tointeger(L, -1);
	pop(L, 1);
	getglobal(L, "ComponentGetValue2");
	pushinteger(L, damage);
	pushstring(L, "air_needed");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "ComponentGetValue2 Error: %s", tolstring(L, -1, NULL));
	bool need = toboolean(L, -1);
	pop(L, 1);
	pushboolean(L, need);
	return 1;
}

int GetPlayerPos(lua_State* L) {
	getglobal(L, "EntityGetWithTag");
	pushstring(L, "player_unit");
	if (pcall(L, 1, 1, 0) != 0)
		return error(L, "EntityGetWithTag Error: %s", tolstring(L, -1, NULL));
	rawgeti(L, -1, 1);
	int player = tointeger(L, -1);
	getglobal(L, "EntityGetTransform");
	pushinteger(L, player);
	if (pcall(L, 1, 2, 0) != 0)
		return error(L, "EntityGetTransform Error: %s", tolstring(L, -1, NULL));
	return 2;
}

int GetPlayerQInventory(lua_State* L) {
	int top = gettop(L);

	getglobal(L, "EntityGetWithTag");
	pushstring(L, "player_unit");
	if (pcall(L, 1, 1, 0) != 0)
		return error(L, "EntityGetWithTag Error: %s", tolstring(L, -1, NULL));
	rawgeti(L, -1, 1);
	int player = tointeger(L, -1);
	getglobal(L, "EntityGetAllChildren");
	pushinteger(L, player);
	if (pcall(L, 1, 1, 0) != 0)
		return error(L, "EntityGetAllChildren Error: %s", tolstring(L, -1, NULL));
	pushnil(L);
	while (next(L, -2) != 0)
	{
		if (type(L, -2) != LUA_TNIL)
		{
			int child = tointeger(L, -1);
			getglobal(L, "EntityGetName");
			pushinteger(L, child);
			if (pcall(L, 1, 1, 0) != 0)
				return error(L, "EntityGetName Error: %s", tolstring(L, -1, NULL));
			if (isstring(L, -1))
			{
				const char* child_name = tolstring(L, -1, NULL);
				if (strcmp(child_name, "inventory_quick") == 0)
				{
					return 2;
				}
			}
			pop(L, 1);
		}
		pop(L, 1);
	}

	settop(L, top);
	pushnil(L);
	return 1;
}

int GetPlayerStomachFullness(lua_State* L) {
	getglobal(L, "EntityGetWithTag");
	pushstring(L, "player_unit");
	if (pcall(L, 1, 1, 0) != 0)
		return error(L, "EntityGetWithTag Error: %s", tolstring(L, -1, NULL));
	rawgeti(L, -1, 1);
	int player = tointeger(L, -1);
	getglobal(L, "EntityGetFirstComponent");
	pushinteger(L, player);
	pushstring(L, "IngestionComponent");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "EntityGetFirstComponent Error: %s", tolstring(L, -1, NULL));
	int stomach = tointeger(L, -1);
	pop(L, 1);
	getglobal(L, "ComponentGetValue2");
	pushinteger(L, stomach);
	pushstring(L, "ingestion_size");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "ComponentGetValue2 Error: %s", tolstring(L, -1, NULL));
	long int size = (long int)tonumber(L, -1);
	pop(L, 1);
	pushnumber(L, size);
	return 1;
}

int GetPlayerStomachSize(lua_State* L) {
	getglobal(L, "EntityGetWithTag");
	pushstring(L, "player_unit");
	if (pcall(L, 1, 1, 0) != 0)
		return error(L, "EntityGetWithTag Error: %s", tolstring(L, -1, NULL));
	rawgeti(L, -1, 1);
	int player = tointeger(L, -1);
	getglobal(L, "EntityGetFirstComponent");
	pushinteger(L, player);
	pushstring(L, "IngestionComponent");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "EntityGetFirstComponent Error: %s", tolstring(L, -1, NULL));
	int stomach = tointeger(L, -1);
	pop(L, 1);
	getglobal(L, "ComponentGetValue2");
	pushinteger(L, stomach);
	pushstring(L, "ingestion_capacity");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "ComponentGetValue2 Error: %s", tolstring(L, -1, NULL));
	long int size = (long int)tonumber(L, -1);
	pop(L, 1);
	pushnumber(L, size);
	return 1;
}

int SetIgnored(lua_State* L) {
	if (gettop(L) != 1 || type(L, 1) != LUA_TBOOLEAN)
		return error(L, "Argument Error: %s", tolstring(L, -1, NULL));

	int b00l = toboolean(L, 1);
	getglobal(L, "EntityGetWithTag");
	pushstring(L, "player_unit");
	if (pcall(L, 1, 1, 0) != 0)
		return error(L, "EntityGetWithTag Error: %s", tolstring(L, -1, NULL));
	rawgeti(L, -1, 1);
	int player = tointeger(L, -1);
	// GenomeSetHerdId is "deprecated", but not really since the game has been untouched for a year or so now
	// if for some reason they do finally remove it, i'll just reinstate it
	getglobal(L, "GenomeSetHerdId");
	pushinteger(L, player);
	if (b00l >= 1)
		pushstring(L, "healer");
	else
		pushstring(L, "player");
	if (pcall(L, 2, 0, 0) != 0)
		return error(L, "GenomeSetHerdId Error: %s", tolstring(L, -1, NULL));
	settop(L, 0);
	return 0;
}

int SetPlayerAir(lua_State* L) {
	if (gettop(L) != 1 || type(L, 1) != LUA_TNUMBER)
		return error(L, "Argument Error: %s", tolstring(L, -1, NULL));

	float air = (float)tonumber(L, 1);
	getglobal(L, "EntityGetWithTag");
	pushstring(L, "player_unit");
	if (pcall(L, 1, 1, 0) != 0)
		return error(L, "EntityGetWithTag Error: %s", tolstring(L, -1, NULL));
	rawgeti(L, -1, 1);
	int player = tointeger(L, -1);
	getglobal(L, "EntityGetFirstComponent");
	pushinteger(L, player);
	pushstring(L, "DamageModelComponent");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "EntityGetFirstComponent Error: %s", tolstring(L, -1, NULL));
	int damage = tointeger(L, -1);
	pop(L, 1);
	getglobal(L, "ComponentSetValue2");
	pushinteger(L, damage);
	pushstring(L, "air_in_lungs");
	pushnumber(L, air);
	if (pcall(L, 3, 0, 0) != 0)
		return error(L, "ComponentSetValue2 Error: %s", tolstring(L, -1, NULL));
	settop(L, 0);
	return 0;
}

int SetPlayerAirM(lua_State* L) {
	if (gettop(L) != 1 || type(L, 1) != LUA_TNUMBER)
		return error(L, "Argument Error: %s", tolstring(L, -1, NULL));

	float air = (float)tonumber(L, 1);
	getglobal(L, "EntityGetWithTag");
	pushstring(L, "player_unit");
	if (pcall(L, 1, 1, 0) != 0)
		return error(L, "EntityGetWithTag Error: %s", tolstring(L, -1, NULL));
	rawgeti(L, -1, 1);
	int player = tointeger(L, -1);
	getglobal(L, "EntityGetFirstComponent");
	pushinteger(L, player);
	pushstring(L, "DamageModelComponent");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "EntityGetFirstComponent Error: %s", tolstring(L, -1, NULL));
	int damage = tointeger(L, -1);
	pop(L, 1);
	getglobal(L, "ComponentSetValue2");
	pushinteger(L, damage);
	pushstring(L, "air_in_lungs_max");
	pushnumber(L, air);
	if (pcall(L, 3, 0, 0) != 0)
		return error(L, "ComponentSetValue2 Error: %s", tolstring(L, -1, NULL));
	settop(L, 0);
	return 0;
}

int SetPlayerClimb(lua_State* L) {
	if (gettop(L) != 1 || type(L, 1) != LUA_TNUMBER)
		return error(L, "Argument Error: %s", tolstring(L, -1, NULL));

	int climb = (float)tointeger(L, 1);
	getglobal(L, "EntityGetWithTag");
	pushstring(L, "player_unit");
	if (pcall(L, 1, 1, 0) != 0) {
		return error(L, "SetPlayerClimb Error: %s", tolstring(L, -1, NULL));
	}
	rawgeti(L, -1, 1);
	int player = tointeger(L, -1);
	getglobal(L, "EntityGetFirstComponent");
	pushinteger(L, player);
	pushstring(L, "CharacterDataComponent");
	if (pcall(L, 2, 1, 0) != 0) {
		return error(L, "SetPlayerClimb Error: %s", tolstring(L, -1, NULL));
	}
	int cdc = tointeger(L, -1);
	getglobal(L, "ComponentSetValue2");
	pushinteger(L, cdc);
	pushstring(L, "climb_over_y");
	pushnumber(L, climb);
	if (pcall(L, 3, 0, 0) != 0) {
		return error(L, "SetPlayerClimb Error: %s", tolstring(L, -1, NULL));
	}
	settop(L, 0);
	return 0;
}

int SetPlayerGold(lua_State* L) {
	if (gettop(L) != 1 || type(L, 1) != LUA_TNUMBER)
		return error(L, "Argument Error: %s", tolstring(L, -1, NULL));

	int mon = (int)tonumber(L, 1);
	getglobal(L, "EntityGetWithTag");
	pushstring(L, "player_unit");
	if (pcall(L, 1, 1, 0) != 0)
		return error(L, "EntityGetWithTag Error: %s", tolstring(L, -1, NULL));
	rawgeti(L, -1, 1);
	int player = tointeger(L, -1);
	getglobal(L, "EntityGetFirstComponent");
	pushinteger(L, player);
	pushstring(L, "WalletComponent");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "EntityGetFirstComponent Error: %s", tolstring(L, -1, NULL));
	int wallet = tointeger(L, -1);
	pop(L, 1);
	getglobal(L, "ComponentSetValue2");
	pushinteger(L, wallet);
	pushstring(L, "money");
	pushinteger(L, mon);
	if (pcall(L, 3, 0, 0) != 0)
		return error(L, "ComponentSetValue2 Error: %s", tolstring(L, -1, NULL));
	settop(L, 0);
	return 0;
}

int SetPlayerHealth(lua_State* L) {
	if (gettop(L) != 1 || type(L, 1) != LUA_TNUMBER)
		return error(L, "Argument Error: %s", tolstring(L, -1, NULL));

	double health = tonumber(L, 1);
	getglobal(L, "EntityGetWithTag");
	pushstring(L, "player_unit");
	if (pcall(L, 1, 1, 0) != 0)
		return error(L, "EntityGetWithTag Error: %s", tolstring(L, -1, NULL));
	rawgeti(L, -1, 1);
	int player = tointeger(L, -1);
	getglobal(L, "EntityGetFirstComponent");
	pushinteger(L, player);
	pushstring(L, "DamageModelComponent");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "EntityGetFirstComponent Error: %s", tolstring(L, -1, NULL));
	int damage = tointeger(L, -1);
	pop(L, 1);
	getglobal(L, "ComponentSetValue2");
	pushinteger(L, damage);
	pushstring(L, "hp");
	pushnumber(L, health / 25);
	if (pcall(L, 3, 0, 0) != 0)
		return error(L, "ComponentSetValue2 Error: %s", tolstring(L, -1, NULL));
	settop(L, 0);
	return 0;
}

int SetPlayerHealthM(lua_State* L) {
	if (gettop(L) != 1 || type(L, 1) != LUA_TNUMBER)
		return error(L, "Argument Error: %s", tolstring(L, -1, NULL));

	double health = tonumber(L, 1);
	getglobal(L, "EntityGetWithTag");
	pushstring(L, "player_unit");
	if (pcall(L, 1, 1, 0) != 0)
		return error(L, "EntityGetWithTag Error: %s", tolstring(L, -1, NULL));
	rawgeti(L, -1, 1);
	int player = tointeger(L, -1);
	getglobal(L, "EntityGetFirstComponent");
	pushinteger(L, player);
	pushstring(L, "DamageModelComponent");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "EntityGetFirstComponent Error: %s", tolstring(L, -1, NULL));
	int damage = tointeger(L, -1);
	pop(L, 1);
	getglobal(L, "ComponentSetValue2");
	pushinteger(L, damage);
	pushstring(L, "max_hp");
	pushnumber(L, health / 25);
	if (pcall(L, 3, 0, 0) != 0)
		return error(L, "ComponentSetValue2 Error: %s", tolstring(L, -1, NULL));
	settop(L, 0);
	return 0;
}

int SetPlayerJetpack(lua_State* L) {
	if (gettop(L) != 1 || type(L, 1) != LUA_TNUMBER)
		return error(L, "Argument Error: %s", tolstring(L, -1, NULL));

	float fly = tonumber(L, 1);
	getglobal(L, "EntityGetWithTag");
	pushstring(L, "player_unit");
	if (pcall(L, 1, 1, 0) != 0)
		return error(L, "EntityGetWithTag Error: %s", tolstring(L, -1, NULL));
	rawgeti(L, -1, 1);
	int player = tointeger(L, -1);
	getglobal(L, "EntityGetFirstComponent");
	pushinteger(L, player);
	pushstring(L, "CharacterDataComponent");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "EntityGetFirstComponent Error: %s", tolstring(L, -1, NULL));
	int cdc = tointeger(L, -1);
	pop(L, 1);
	getglobal(L, "ComponentSetValue2");
	pushinteger(L, cdc);
	pushstring(L, "fly_time_max");
	pushnumber(L, fly);
	if (pcall(L, 3, 0, 0) != 0)
		return error(L, "ComponentSetValue2 Error: %s", tolstring(L, -1, NULL));
	settop(L, 0);
	return 0;
}

int SetPlayerNeedsAir(lua_State* L) {
	if (gettop(L) != 1 || type(L, 1) != LUA_TBOOLEAN)
		return error(L, "Argument Error: %s", tolstring(L, -1, NULL));

	bool needed = toboolean(L, 1);
	getglobal(L, "EntityGetWithTag");
	pushstring(L, "player_unit");
	if (pcall(L, 1, 1, 0) != 0)
		return error(L, "EntityGetWithTag Error: %s", tolstring(L, -1, NULL));
	rawgeti(L, -1, 1);
	int player = tointeger(L, -1);
	getglobal(L, "EntityGetFirstComponent");
	pushinteger(L, player);
	pushstring(L, "DamageModelComponent");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "EntityGetFirstComponent Error: %s", tolstring(L, -1, NULL));
	int damage = tointeger(L, -1);
	pop(L, 1);
	getglobal(L, "ComponentSetValue2");
	pushinteger(L, damage);
	pushstring(L, "air_needed");
	pushboolean(L, needed);
	if (pcall(L, 3, 0, 0) != 0)
		return error(L, "ComponentSetValue2 Error: %s", tolstring(L, -1, NULL));
	settop(L, 0);
	return 0;
}

int SetPlayerPos(lua_State* L) {
	if (gettop(L) != 2 || type(L, 1) != LUA_TNUMBER && type(L, 2) != LUA_TNUMBER)
		return error(L, "Argument Error: %s", tolstring(L, -1, NULL));

	int x = tonumber(L, 1);
	int y = tonumber(L, 2);
	getglobal(L, "EntityGetWithTag");
	pushstring(L, "player_unit");
	if (pcall(L, 1, 1, 0) != 0)
		return error(L, "EntityGetWithTag Error: %s", tolstring(L, -1, NULL));
	rawgeti(L, -1, 1);
	int player = tointeger(L, -1);
	getglobal(L, "EntitySetTransform");
	pushinteger(L, player);
	pushnumber(L, x);
	pushnumber(L, y);
	pushnumber(L, 0);
	pushnumber(L, 1);
	pushnumber(L, 1);
	if (pcall(L, 6, 0, 0) != 0)
		return error(L, "EntitySetTransform Error: %s", tolstring(L, -1, NULL));
	settop(L, 0);
	return 0;
}

int SetPlayerStomachFullness(lua_State* L) {
	if (gettop(L) != 1 || type(L, 1) != LUA_TNUMBER)
		return error(L, "Argument Error: %s", tolstring(L, -1, NULL));

	long int stomach = tonumber(L, 1);
	getglobal(L, "EntityGetWithTag");
	pushstring(L, "player_unit");
	if (pcall(L, 1, 1, 0) != 0)
		return error(L, "EntityGetWithTag Error: %s", tolstring(L, -1, NULL));
	rawgeti(L, -1, 1);
	int player = tointeger(L, -1);
	getglobal(L, "EntityGetFirstComponent");
	pushinteger(L, player);
	pushstring(L, "IngestionComponent");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "EntityGetFirstComponent Error: %s", tolstring(L, -1, NULL));
	int ingestion = tointeger(L, -1);
	pop(L, 1);
	getglobal(L, "ComponentSetValue2");
	pushinteger(L, ingestion);
	pushstring(L, "ingestion_size");
	pushnumber(L, stomach);
	if (pcall(L, 3, 0, 0) != 0)
		return error(L, "ComponentSetValue2 Error: %s", tolstring(L, -1, NULL));
	settop(L, 0);
	return 0;
}

int SetPlayerStomachSize(lua_State* L) {
	if (gettop(L) != 1 || type(L, 1) != LUA_TNUMBER)
		return error(L, "Argument Error: %s", tolstring(L, -1, NULL));

	long int stomach = tonumber(L, 1);
	getglobal(L, "EntityGetWithTag");
	pushstring(L, "player_unit");
	if (pcall(L, 1, 1, 0) != 0)
		return error(L, "EntityGetWithTag Error: %s", tolstring(L, -1, NULL));
	rawgeti(L, -1, 1);
	int player = tointeger(L, -1);
	getglobal(L, "EntityGetFirstComponent");
	pushinteger(L, player);
	pushstring(L, "IngestionComponent");
	if (pcall(L, 2, 1, 0) != 0)
		return error(L, "EntityGetFirstComponent Error: %s", tolstring(L, -1, NULL));
	int ingestion = tointeger(L, -1);
	pop(L, 1);
	getglobal(L, "ComponentSetValue2");
	pushinteger(L, ingestion);
	pushstring(L, "ingestion_capacity");
	pushnumber(L, stomach);
	if (pcall(L, 3, 0, 0) != 0)
		return error(L, "ComponentSetValue2 Error: %s", tolstring(L, -1, NULL));
	settop(L, 0);
	return 0;
}

// Task library
int ExecuteThroughLoader(lua_State* L) {
	if (gettop(L) != 1 || type(L, 1) != LUA_TSTRING)
		return error(L, "Argument Error: %s", tolstring(L, -1, NULL));

	const char* script = tolstring(L, 1, NULL);
	getglobal(L, "EntityGetWithTag");
	pushstring(L, "player_unit");
	if (pcall(L, 1, 1, 0) != 0)
		return error(L, "EntityGetWithTag Error: %s", tolstring(L, -1, NULL));
	rawgeti(L, -1, 1);
	int player = tointeger(L, -1);
	getglobal(L, "EntityGetFirstComponent");
	pushinteger(L, player);
	pushstring(L, "LuaComponent");
	if (pcall(L, 2, 1, 0) != 0) {
		return error(L, "EntityGetFirstComponent Error: %s", tolstring(L, -1, NULL));
	}
	int lua = tointeger(L, -1);
	pop(L, 1);
	getglobal(L, "ModTextSetFileContent");
	pushstring(L, "data/scripts/empty.lua");
	std::string skript = script;
	std::string encode = "\nComponentSetValue2(og_lua, 'enable_coroutines', '0'); ComponentSetValue2(og_lua, 'vm_type', 'ONE_PER_COMPONENT_INSTANCE'); ComponentSetValue2(og_lua, 'execute_every_n_frame', 80); ComponentSetValue2(og_lua, 'script_source_file', 'data/scripts/magic/player_biome_check.lua'); ModTextSetFileContent('data/scripts/empty.lua','');";
	std::string code = "local og_lua = EntityGetFirstComponent(LocalPlayer.GetID(),'LuaComponent');\n" + skript + encode;
	pushstring(L, code.c_str());
	if (pcall(L, 2, 0, 0) != 0)
		return error(L, "ModTextSetFileContent Error: %s", tolstring(L, -1, NULL));
	getglobal(L, "ComponentSetValue2");
	pushinteger(L, lua);
	pushstring(L, "vm_type");
	pushstring(L, "CREATE_NEW_EVERY_EXECUTION");
	if (pcall(L, 3, 0, 0) != 0)
		return error(L, "ComponentSetValue2 Error: %s", tolstring(L, -1, NULL));
	getglobal(L, "ComponentSetValue2");
	pushinteger(L, lua);
	pushstring(L, "enable_coroutines");
	pushinteger(L, 1);
	if (pcall(L, 3, 0, 0) != 0)
		return error(L, "ComponentSetValue2 Error: %s", tolstring(L, -1, NULL));
	getglobal(L, "ComponentSetValue2");
	pushinteger(L, lua);
	pushstring(L, "script_source_file");
	pushstring(L, "data/scripts/empty.lua");
	if (pcall(L, 3, 0, 0) != 0)
		return error(L, "ComponentSetValue2 Error: %s", tolstring(L, -1, NULL));
	getglobal(L, "ComponentSetValue2");
	pushinteger(L, lua);
	pushstring(L, "execute_every_n_frame");
	pushinteger(L, 1);
	if (pcall(L, 3, 0, 0) != 0)
		return error(L, "ComponentSetValue2 Error: %s", tolstring(L, -1, NULL));
	settop(L, 0);
	return 0;
}

int ForceIsBetaBuild(lua_State* L) {
	if (gettop(L) != 1 || type(L, 1) != LUA_TBOOLEAN)
		return error(L, "Argument Error: %s", tolstring(L, -1, NULL));

	bool beta = toboolean(L, 1);
	if (beta == true)
	{
		writeINT(noita_base + nlua_offsets::isbetabuild, 0);
	}
	else {
		writeINT(noita_base + nlua_offsets::isbetabuild, 1);
	}
	return 0;
}

int GetCFunctionPointer(lua_State* L) {
	if (gettop(L) != 1 || !iscfunction(L, 1))
		return error(L, "Argument Error: %s", tolstring(L, -1, NULL));

	lua_CFunction func = tocfunction(L, 1);
	pushinteger(L, (uintptr_t)func);
	return 1;
}

int GetState(lua_State* L) {
	pushinteger(L, (uintptr_t)L);
	return 1;
}