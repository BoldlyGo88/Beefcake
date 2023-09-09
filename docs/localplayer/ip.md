# LocalPlayer.IsPolymorphed

```lua
local is_poly,entity = LocalPlayer.IsPolymorphed();

if is_poly then
	GamePrint(entity);
end;
```

# Description

Returns if the player is currently polymorphed or not, and if they currently are it returns their temporary entity id

# Parameters

N/A

# Return Value

Returns true or false if the player is polymorphed, if the former it also returns the temporary entity id