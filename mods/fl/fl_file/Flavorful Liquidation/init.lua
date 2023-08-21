function OnPlayerSpawned(player_entity)		
	if not EntityGetChild(player_entity, 'PEE_ENTITY') then
		local pee = EntityLoad('data/pee/Pee.xml');
		EntityAddChild(player_entity, pee);
	end;
end;
