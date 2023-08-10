# AddSpellToWand

```lua
local wand = CreateWand({mana_max = 1000, mana_charge_speed = 750,},{actions_per_round = 1},{ui_name = "TEST_WAND"});

AddSpellToWand(wand, "BLACK_HOLE", true);
AddSpellToWand(wand, "BOMB_HOLY", false);
```

# Description

Adds a spell to the passed wand. The spell can be either permanent or swappable

# Parameters

- wand: the entity id of the wand ***[int]***
- spell: the string spell id ***[string]***
- permanent: is the spell permanent or swappable ***[bool]***

# Return Value

N/A

# Warning

***This function is restricted from direct use in the Beefcake Console, it must be wrapped inside of task.ExecuteTL() if used within the console.***
