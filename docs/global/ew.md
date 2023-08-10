# EditWand

```lua
local wand = CreateWand({},{},{});

EditWand(wand,
{
 mana_max = 1000,
 mana_charge_speed = 750,
 reload_time_frames = (4 / rfd),
 item_recoil_max = -100,
 cast_delay = (2 / cdd)
},
{
actions_per_round = 1,
reload_time = (4 / rfd),
deck_capacity = 4
},
{
ui_name = "TEST_WAND",
sprite = "data/items_gfx/wands/wand_0050.png",
offset_x = 4,
offset_y = 8
});
```

# Description

Edit the given wand with the desired properties

# Parameters

- wand_id: the entity id of the wand to edit ***[int]***
- ability_components: table of AbilityComponent values to set ***[table]***
- gunaction_components: table of gunaction component values to set ***[table]***
- sprite_components: table of sprite component values to set ***[table]***

*Valid AbilityComponent(s):*
- cast_delay: the wands cast delay, value ratio 1:0.0165 ***[double]***
- item_recoil_max: the wands recoil ***[double]***
- mana_charge_speed: speed at which the mana will recharge after every shot ***[double]***
- mana_max: max mana the wand will hold ***[double]***
- reload_time_frames: recharge time for the wand, value ratio 1:0.0167 ***[double]***

*Valid GunAction(s):*
- actions_per_round: how many spells the wand will shoot per shot ***[int]***
- deck_capacity: how many spells the wand can hold ***[int]***
- reload_time: recharge time for the wand, value ratio 1:0.0167 ***[double]***

*Valid SpriteComponents(s):*
- offset_x: the wand sprites graphics x offset ***[int]***
- offset_y: the wand sprites graphics y offset ***[int]***
- sprite: the wand sprites graphics file ***[string]***
- ui_name: the wands name ***[string]***

# Return Value

N/A

# Warning

***This function is restricted from direct use in the Beefcake Console, it must be wrapped inside of task.ExecuteTL() if used within the console.***
