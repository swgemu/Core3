radanthus_mandelatara_missions =
	{
	-- Missing quest text strings. Placeholder screenplay for future (npc will spawn and say "notyet" string for now
	}

npcMapRadanthusMandelatara =
	{
		{
			spawnData = { npcTemplate = "radanthus_mandelatara", x = -4.0, z = 1.6, y = -10.7, direction = -82, cellID = 1717473, position = STAND },
			worldPosition = { x = 4645.5, y = -4890 },
			npcNumber = 1,
			stfFile = "@static_npc/naboo/radanthus_mandelatara",
			missions = radanthus_mandelatara_missions
		}
	}

RadanthusMandelatara = ThemeParkLogic:new {
	npcMap = npcMapRadanthusMandelatara,
	className = "RadanthusMandelatara",
	screenPlayState = "radanthus_mandelatara_quest",
	planetName = "naboo"
}

registerScreenPlay("RadanthusMandelatara", true)

radanthus_mandelatara_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = RadanthusMandelatara
}
