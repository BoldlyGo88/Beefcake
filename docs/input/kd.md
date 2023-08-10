# input.KeyDown

```lua
if input.KeyDown("E") then
	GamePrint("E is being pressed!");
end;
```

# Description

Returns true if the given key is being pressed

# Parameters

- key: the key ***[string]***

# Return Value

Returns true or false depending on if the key is pressed

# Warning

***This function should be called from a script thats running every frame, it will likely not work correctly otherwise.***
