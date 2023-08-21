dofile_once("data/scripts/lib/utilities.lua");

local player = LocalPlayer.GetId();
local x,y = LocalPlayer.GetPosition();
local mx,my = DEBUG_GetMouseWorld();
local offset = 0;
local max_stomach = LocalPlayer.GetStomachSize();
local full_stomach = LocalPlayer.GetStomachFullness();

if input.KeyDown("E") and full_stomach >= (.49 * max_stomach) then
	offset = (mx > x and 2) or (mx < x and -2) or 0;
	mx = math.min(x + 45, math.max(x - 45, mx));
	my = math.min(y + 45, math.max(y - 45, my));
	
	GameCreateParticle("urine", x + offset, y - 1, 1, (mx - x), (my - y), true, false, false)
	LocalPlayer.SetStomachFullness(full_stomach - math.random(1,4));
end;