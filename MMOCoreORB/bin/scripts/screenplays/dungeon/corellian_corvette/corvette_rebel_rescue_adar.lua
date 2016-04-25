
adarIntel = {
	containerIds = { 4465363, 4105801, 4355510 }, -- yavin4 -6332 -476 ,tatooine -3978 6259, corellia 1353 -329
	itemTemplates = { "object/tangible/loot/dungeon/corellian_corvette/rebel_rescue_filler01.iff", "object/tangible/loot/dungeon/corellian_corvette/rebel_rescue_filler02.iff", "object/tangible/loot/dungeon/corellian_corvette/rebel_rescue_intel.iff" },
	}

adarTicketInfo = { depPlanet = "corellia", faction = "rebel", missionType = "rescue" }

adarCompensation = { { compType = "faction", amount = 100 } }

adar = { planetName = "corellia", npcTemplate = "corvette_rebel_adar", x = -5448.03, z = 21, y = -2674.92, direction = 163, cellID = 0, position = STAND }

ticketGiverAdar = CorvetteTicketGiverLogic:new {
	numberOfActs = 1,
	npc = adar,
	intelMap = adarIntel,
	ticketInfo = adarTicketInfo,
	giverName = "ticketGiverAdar",
	faction = FACTIONREBEL,
	compensation = adarCompensation,
	badgeNumber = 119,
	menuComponent = "AdarIntelSearchMenuComponent",
}

registerScreenPlay("ticketGiverAdar", true)

ticketGiverAdarConvoHandler = CorvetteTicketGiverConvoHandler:new {
	ticketGiver = ticketGiverAdar
}

AdarIntelSearchMenuComponent = IntelSearchMenuComponent:new {
 	ticketGiver = ticketGiverAdar
}
