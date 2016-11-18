brass_marshoo_missions =
	{
	-- Missing quest text strings. Placeholder screenplay for future (npc will spawn and say "notyet" string for now
	}

npcMapBrassMarshoo =
	{
		{
			spawnData = { npcTemplate = "brass_marshoo", x = -5629.4, z = -156.2, y = -3.4, direction = -82, cellID = 0, position = STAND },
			npcNumber = 1,
			stfFile = "@static_npc/naboo/brass_marshoo",
			missions = brass_marshoo_missions
		}
	}

BrassMarshoo = ThemeParkLogic:new {
	npcMap = npcMapBrassMarshoo,
	className = "BrassMarshoo",
	screenPlayState = "brass_marshoo_quest",
	planetName = "naboo"
}

registerScreenPlay("BrassMarshoo", true)

brass_marshoo_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = BrassMarshoo
}
