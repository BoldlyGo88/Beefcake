# SpawnSpell

```lua
local x,y = LocalPlayer.GetPosition();

SpawnSpell("BLACK_HOLE", x, y);
```

# Description

Spawns a spell at the given location

# Parameters

- spell_id: the spell id ***[string]***
- x_position: the x position to spawn the spell at ***[int]***
- y_position: the y position to spawn the spell at ***[int]***

# Return Value

N/A

# Warning

***This function is restricted from direct use in the Beefcake Console, it must be wrapped inside of task.ExecuteTL() if used within the console.***
