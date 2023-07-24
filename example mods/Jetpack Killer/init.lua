dofile_once("data/scripts/lib/utilities.lua")

function OnPlayerSpawned(player_entity)	
	local inventory = LocalPlayer.GetInventory();
	
	if inventory then
		local items = EntityGetAllChildren(inventory);

		if items then
			for __,_ in ipairs(items) do
				GameKillInventoryItem(player_entity, _);
			end;
		end;
	end;
	
	EntityLoad("data/jpk/KillerJetpackLoader.xml");
	
	GamePrintImportant("Exploited by The Gods", "The Gods have decided to test something on you..");
end
