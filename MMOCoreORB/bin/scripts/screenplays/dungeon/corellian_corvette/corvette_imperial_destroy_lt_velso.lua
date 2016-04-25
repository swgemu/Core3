
velsoIntel =	{
			containerIds = { 4305488, 4465373, 3795407 }, -- corellia -2659 3003 , dantooine 7197 -4090, talus 2143 -5649
			itemTemplates = { "object/tangible/loot/dungeon/corellian_corvette/imperial_destroy_filler01.iff", "object/tangible/loot/dungeon/corellian_corvette/imperial_destroy_filler02.iff", "object/tangible/loot/dungeon/corellian_corvette/imperial_destroy_intel.iff" },
		}

velsoTicketInfo = { depPlanet = "tatooine", faction = "imperial", missionType = "destroy" }

velsoCompensation = { { compType = "credits", amount = 500 } }

lt_velso = { planetName = "naboo", npcTemplate = "lt_velso", x = 23.4, z = .2, y = -19.4, direction = 180, cellID = 1418874, position = STAND, mood = "npc_imperial"}

ticketGiverVelso = CorvetteTicketGiverLogic:new {
	numberOfActs = 1,
	npc = lt_velso,
	intelMap = velsoIntel,
	ticketInfo = velsoTicketInfo,
	giverName = "ticketGiverVelso",
	faction = 0,
	compensation = velsoCompensation,
	badgeNumber = 112,
	menuComponent = "VelsoIntelSearchMenuComponent",
}

registerScreenPlay("ticketGiverVelso", true)

ticketGiverVelsoConvoHandler = CorvetteTicketGiverConvoHandler:new {
	ticketGiver = ticketGiverVelso
}

VelsoIntelSearchMenuComponent = IntelSearchMenuComponent:new {
	ticketGiver = ticketGiverVelso
}
