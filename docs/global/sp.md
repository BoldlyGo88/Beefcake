# SpawnPerk

```lua
local x,y = LocalPlayer.GetPosition();

SpawnPerk("CRITICAL_HIT", x, y);
```

# Description

Spawns a perk at the given location

# Parameters

- perk_id: the perk id ***[string]***
- x_position: the x position to spawn the perk at ***[int]***
- y_position: the y position to spawn the perk at ***[int]***

# Return Value

N/A

# Warning

***This function is restricted from direct use in the Beefcake Console, it must be wrapped inside of task.ExecuteTL() if used within the console.***