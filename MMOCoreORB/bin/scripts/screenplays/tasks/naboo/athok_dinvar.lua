athok_dinvar_missions =
	{
	-- Missing quest text strings. Placeholder screenplay for future (npc will spawn and say "notyet" string for now
	}

npcMapAthokDinvar =
	{
		{
			spawnData = { npcTemplate = "athok_dinvar", x = -5.4, z = -4.9, y = -1.2, direction = -179, cellID = 1685077, position = STAND },
			worldPosition = { x = 1607.8, y = 2499.4 },
			npcNumber = 1,
			stfFile = "@static_npc/naboo/athok_dinvar",
			missions = athok_dinvar_missions
		}
	}

AthokDinvar = ThemeParkLogic:new {
	npcMap = npcMapAthokDinvar,
	className = "AthokDinvar",
	screenPlayState = "athok_dinvar_quest",
	planetName = "naboo"
}

registerScreenPlay("AthokDinvar", true)

athok_dinvar_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = AthokDinvar
}
