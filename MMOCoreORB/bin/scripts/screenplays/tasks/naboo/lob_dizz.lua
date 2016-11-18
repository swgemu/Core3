lob_dizz_missions =
	{
	-- Missing quest text strings. Placeholder screenplay for future (npc will spawn and say "notyet" string for now
	}

npcMapLobDizz =
	{
		{
			spawnData = { npcTemplate = "lob_dizz", x = -1965.5, z = 6.2, y = -5391.6, direction = -109, cellID = 0, position = STAND },
			npcNumber = 1,
			stfFile = "@static_npc/naboo/lob_dizz",
			missions = lob_dizz_missions
		}
	}

LobDizz = ThemeParkLogic:new {
	npcMap = npcMapLobDizz,
	className = "LobDizz",
	screenPlayState = "lob_dizz_quest",
	planetName = "naboo"
}

registerScreenPlay("LobDizz", true)

lob_dizz_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = LobDizz
}
