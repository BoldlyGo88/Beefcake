# GenomeGetHerdId

```lua
local player = LocalPlayer.GetId();
local herd_id = GenomeGetHerdId(player);

if herd_id == "player" then
  LocalPlayer.SetIsIgnored(true);
end;
```

# Description

Gets the entities herd id

# Parameters

- entity: the entity id to get the herd id from ***[int]***

# Return Value

Returns the given entities herd id