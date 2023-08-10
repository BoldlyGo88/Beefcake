# ModTextFileGetContent

```lua
ModTextSetFileContent("data/scripts/empty.lua", "GamePrint('test');");

local file = ModTextFileGetContent("data/scripts/empty.lua");
task.ExecuteTL(file);
```

# Description

Gets the content of a filename

# Parameters

- filename: file path to read from ***[string]***

# Return Value

Returns a string containing the files contents
