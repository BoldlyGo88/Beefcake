function OnPlayerSpawned( player_entity )
SetWorldTime(1)								        -- Change TimeOfDay to day
LocalPlayer.SetIsIgnored(true); 			        -- Make all enemies ignore the player
LocalPlayer.SetGold(inf); 			                -- Give the player infinite amount of gold
-- Give the player perks 
LocalPlayer.AddPerk("BREATH_UNDERWATER");
LocalPlayer.AddPerk("MOVEMENT_FASTER");
LocalPlayer.AddPerk("FASTER_LEVITATION");
LocalPlayer.AddPerk("REMOVE_FOG_OF_WAR");
LocalPlayer.AddPerk("PROTECTION_FIRE");
LocalPlayer.AddPerk("PROTECTION_RADIOACTIVITY");
LocalPlayer.AddPerk("PROTECTION_EXPLOSION");
LocalPlayer.AddPerk("PROTECTION_MELEE");
LocalPlayer.AddPerk("PROTECTION_ELECTRICITY");
LocalPlayer.AddPerk("EDIT_WANDS_EVERYWHERE");
LocalPlayer.AddPerk("ADVENTURER");
LocalPlayer.AddPerk("UNLIMITED_SPELLS");
LocalPlayer.AddPerk("EXTRA_PERK");
LocalPlayer.AddPerk("PERKS_LOTTERY");
LocalPlayer.AddPerk("EXTRA_SHOP_ITEM");
print("Explorer Mode activated!");
end