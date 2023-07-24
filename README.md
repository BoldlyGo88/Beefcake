# Beefcake

Beefcake is an attempt to expand Noitas modding API to make it more user-friendly and to remove many
of the restrictions imposed by the original.

Beefcake uses Noitas existing modloader (which means it supports ALL existing mods) and includes plenty
of custom functions to make coding less bloated and easier to read.

Latest release supported version: Jun 19 2023 Build

Latest compiled supported version: Jun 19 2023 Build

## Setting up

### Prerequisites

As of right now Beefcake has only been tested with the Steam version of Noita, it is likely it will
not work with other versions.
- [Noita on Steam](https://store.steampowered.com/app/881100/Noita/)

For the average users (people wanting to mod, or use mods) setting up Beefcake is pretty easy, and replaces no files.

1. Navigate to Noitas directory

![](https://github.com/WadeBA/Beefcake/blob/main/exampleimg/example1.png)

2. Create a new folder named "beefcake" inside of Noitas directory

![](https://github.com/WadeBA/Beefcake/blob/main/exampleimg/example2.png)

3. Download and extract both Beefcake.exe (the loader) and beefer.dll (the main api) into the folder you created in step 2

![](https://github.com/WadeBA/Beefcake/blob/main/exampleimg/example3.png)

4. Open Steam and navigate to Noitas properties

![](https://github.com/WadeBA/Beefcake/blob/main/exampleimg/example4.png)

5. Under general and in the launch options box put (or whatever path corresponds to the location of Beefcake.exe and beefer.dll):
```
"C:\Program Files (x86)\Steam\steamapps\common\Noita\beefcake\Beefcake.exe" %command%
```

![](https://github.com/WadeBA/Beefcake/blob/main/exampleimg/example5.png)

6. Run Noita from Steam, and once the console is open enter the path to Noita (one time thing)

![](https://github.com/WadeBA/Beefcake/blob/main/exampleimg/example6.png)

7. Enjoy modding!

Once the console is open, you may notice it says "Waiting for MAPITable to initiate.." this is normal and will continue once a game is started!

## License

This project is licensed under the [MIT License](LICENSE.md)

As a developer you get control over:
- Commercial use
- Modification
- Distribution
- Private use 

Find out more information about the [MIT License](LICENSE.md)

## Acknowledgments

  - The developers of [Noita](https://store.steampowered.com/app/881100/Noita/), [Nolla Games](https://nollagames.com/)
  - The developer of [libmem](https://github.com/rdbo/libmem), [rdbo](https://github.com/rdbo)
  - The developer of [color-console](https://github.com/aafulei/color-console), [aafulei](https://github.com/aafulei)
 
## Documentation

#### Beefcake Globals
- AddSpellToWand(wand_entity: int, spell_id: string, is_always_cast: boolean)
```lua
local wand = CreateWand("EXAMPLE_WAND", "data/items_gfx/wands/wand_0007.png", 250, 1000, 0.45, 0.2, 1, 3);
AddSpellToWand(wand, "BLACK_HOLE", true);
```
- CreateWand(name: string, wand_image_path: string, mana_charge: number, mana_max: number, reload_speed: number, recoil: number, spell_per_shot: int, capacity: int)
```lua
local wand = CreateWand("EXAMPLE_WAND", "data/items_gfx/wands/wand_0007.png", 250, 1000, 0.45, 0.2, 1, 3);

-- if mana_charge is zero or nil it defaults to 100
-- if mana_max is zero or nil it defaults to 75
```
- ExecuteThroughLoader(script: string)
```lua
ExecuteThroughLoader("local x,y = LocalPlayer.GetPosition(); EntityLoad('data/entities/flute.xml',x,y);");

-- its recommended this function is used ONLY in the Beefcake Console, it executes code through a LuaComponent avoiding many visual and memory bugs.
-- using it in mod files may have unwanted side effects
```
- ForceSeed(seed: int)
```lua
function OnModPreInit()
ForceSeed(123456789);
end;

-- its recommended this function is used ONLY in the OnModPreInit() function of the mods init.lua file
-- using it in other functions or files may have unwanted side effects, or likely to not work at all
```
- GenomeGetHerdId(entity_id: int)
```lua
local player = LocalPlayer.GetID();
local herd_id = GenomeGetHerdId(player);

if herd_id == "player" then
  LocalPlayer.SetIsIgnored(true);
end;
```
- inf
```lua
LocalPlayer.SetGold(inf);
LocalPlayer.SetMaxHealth(inf);
LocalPlayer.SetHealth(inf);

-- a global variable that is 1:1 with noitas "infinite" value, showing as an infinite symbol
```
- SetWorldTime(time: double)
```lua
SetWorldTime(1.0);   -- day

-- time ranges from 0.0 to 1.0
```
- SpawnFlask(material_id: string, x_pos: number, y_pos: number, amount: number)
```lua
local x,y = LocalPlayer.GetPosition();

SpawnFlask("lava", x, y, 1000);

-- Flasks full value is 1000, 500 is halfway, etc..
-- Values higher than 1000 work and give the shooting more "pressure"
```
- SpawnPerk(perk_id: string, x_pos: number, y_pos: number)
```lua
local x,y = LocalPlayer.GetPosition();

SpawnPerk("CRITICAL_HIT", x, y);
```
- SpawnSpell(spell_id: string, x_pos: number, y_pos: number)
```lua
local x,y = LocalPlayer.GetPosition();

SpawnSpell("BLACK_HOLE", x, y);
```

#### LocalPlayer Library
- LocalPlayer.AddPerk(perk_id: string)
```lua
LocalPlayer.AddPerk("CRITICAL_HIT");

-- unlike SpawnPerk, LocalPlayer.AddPerk gives the perk directly to the player
```
- LocalPlayer.GetGold()
```lua
local gold = LocalPlayer.GetGold();

-- returns the players gold
```
- LocalPlayer.GetHealth()
```lua
local health = LocalPlayer.GetHealth();

-- returns the players health
```
- LocalPlayer.GetID()
```lua
local player = LocalPlayer.GetID();

-- returns the players entity id
```
- LocalPlayer.GetInventory()
```lua
local player = LocalPlayer.GetID();
local inventory = LocalPlayer.GetInventory();

if inventory then
  local items = EntityGetAllChildren(inventory);

  if items then
    for i, item in ipairs(items) do
      GameKillInventoryItem(player, item);
    end;
  end;
end;

-- returns the players "quick" inventory
```
- LocalPlayer.GetIsIgnored()
```lua
if LocalPlayer.GetIsIgnored() then
  print("Enemies are ignoring the player!");
else
  print("Enemies are not ignoring the player!");
end;

-- returns if the player is currently ignored by enemies or not
```
- LocalPlayer.GetMaxHealth()
```lua
local max_health = LocalPlayer.GetMaxHealth();

-- returns the players max health
```
- LocalPlayer.GetPosition()
```lua
local x,y = LocalPlayer.GetPosition();

-- returns the players x and y position
```
- LocalPlayer.SetGold(gold: int)
```lua
LocalPlayer.SetGold(inf);
```
- LocalPlayer.SetHealth(health: number)
```lua
LocalPlayer.SetHealth(100);
LocalPlayer.SetMaxHealth(1000);
LocalPlayer.SetHealth(1000);

-- health can only be as high as its max healh
-- if the players max health is 100, setting health to 1000 will not work unless setting max health before
```
- LocalPlayer.SetIsIgnored(is_ignored: boolean)
```lua
LocalPlayer.SetIsIgnored(true);

-- this determines if enemies will ignore the player or not
```
- LocalPlayer.SetMaxHealth(health: number)
```lua
LocalPlayer.SetMaxHealth(1000);
```
- LocalPlayer.SetPosition(x_pos: int, y_pos: int)
```lua
LocalPlayer.SetPosition(100, -50);
```

#### Task Library
- task.GetCFunctionPointer(c_function: function)
```lua
print(string.format("%x", task.GetCFunctionPointer(EntityLoad)));

-- prints the memory address of the noita function EntityLoad
-- this WILL NOT work with lua functions, only functions made in C
```
- task.GetState()
```lua
print(string.format("%x", task.GetState()));

-- prints the memory address of current lua state
```
- task.ReadMemory(address: int, type: int)
```lua
local current_seed = task.ReadMemory(0x00FEE850, 0);
local build_text = task.ReadMemory(0x00E1C3B8, 1);

-- current valid types:
-- 0 = int
-- 1 = string
```
