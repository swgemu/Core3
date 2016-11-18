bab_esrus_missions =
	{
	-- Missing quest text strings. Placeholder screenplay for future (npc will spawn and say "notyet" string for now
	}

npcMapBabEsrus =
	{
		{
			spawnData = { npcTemplate = "bab_esrus", x = 4836.8, z = 3.8, y = -4836.3, direction = -124, cellID = 0, position = STAND },
			npcNumber = 1,
			stfFile = "@static_npc/naboo/bab_esrus",
			missions = bab_esrus_missions
		}
	}

BabEsrus = ThemeParkLogic:new {
	npcMap = npcMapBabEsrus,
	className = "BabEsrus",
	screenPlayState = "bab_esrus_quest",
	planetName = "naboo"
}

registerScreenPlay("BabEsrus", true)

bab_esrus_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = BabEsrus
}
