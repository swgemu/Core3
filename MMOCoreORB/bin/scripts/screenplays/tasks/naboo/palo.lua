palo_missions =
	{
	-- Missing quest text strings. Placeholder screenplay for future (npc will spawn and say "notyet" string for now
	}

npcMapPalo =
	{
		{
			spawnData = { npcTemplate = "palo", x = 4762.9, z = 6.1, y = -4796.0, direction = -12, cellID = 0, position = STAND },
			npcNumber = 1,
			stfFile = "@static_npc/naboo/palo",
			missions = palo_missions
		}
	}

Palo = ThemeParkLogic:new {
	npcMap = npcMapPalo,
	className = "Palo",
	screenPlayState = "palo_quest",
	planetName = "naboo"
}

registerScreenPlay("Palo", true)

palo_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = Palo
}
