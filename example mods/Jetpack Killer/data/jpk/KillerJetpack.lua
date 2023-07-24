dofile_once("data/scripts/lib/utilities.lua");

local player = LocalPlayer.GetID();
local x,y = LocalPlayer.GetPosition();
local platformingcomp = EntityGetFirstComponent(player, "CharacterPlatformingComponent");

if not platformingcomp or ComponentGetValue2(platformingcomp, "mJetpackEmitting") < 1 then
	return;
end;

local velx,vely = GameGetVelocityCompVelocity(player);
velx = -velx * 75;
vely = -vely * 50;

local trail = shoot_projectile(player, "data/jpk/KillerTrail.xml", x, y, velx, vely);
local projectilecomp = EntityGetComponent(trail, "ProjectileComponent");

if projectilecomp then
	EntityAddComponent(trail, "HomingComponent", {homing_targeting_coeff = "100.0", homing_velocity_multiplier = "0.80", detect_distance="100", });
end;