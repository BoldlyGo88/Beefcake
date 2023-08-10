# LocalPlayer.GetInventory

```lua
local player = LocalPlayer.GetId();
local inventory = LocalPlayer.GetInventory();

if inventory then
	local items = EntityGetAllChildren(inventory);
	
	if items then
		for i, item in ipairs(item) do
			GameKillInventoryItem(player, item);
		end;
	end;
end;
```

# Description

Gets the players inventory entity id

# Parameters

N/A

# Return Value

Returns the players inventory entity id