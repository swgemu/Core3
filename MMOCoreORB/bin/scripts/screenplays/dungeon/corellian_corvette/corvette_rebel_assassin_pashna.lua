
pashnaIntel = {
	containerIds = { 4245460, 4015451, 4305478 }, -- yavin4 -6332 -476 ,tatooine -3978 6259, corellia 1353 -329
	itemTemplates = { "object/tangible/loot/dungeon/corellian_corvette/rebel_assassin_filler01.iff", "object/tangible/loot/dungeon/corellian_corvette/rebel_assassin_filler02.iff", "object/tangible/loot/dungeon/corellian_corvette/rebel_assassin_intel.iff" },
}

pashnaTicketInfo = { depPlanet = "corellia", faction = "rebel", missionType = "assassin" }

pashnaCompensation = { { compType = "faction", amount = 100 } }

pashna = { planetName = "corellia", npcTemplate = "corvette_rebel_pashna", x = 6772.57, z = 315, y = -5697.8, direction = 245, cellID = 0, position = STAND }

ticketGiverPashna = CorvetteTicketGiverLogic:new {
	numberOfActs = 1,
	npc = pashna,
	intelMap = pashnaIntel,
	ticketInfo = pashnaTicketInfo,
	giverName = "ticketGiverPashna",
	faction = FACTIONREBEL,
	compensation = pashnaCompensation,
	badgeNumber = 120,
	menuComponent = "PashnaIntelSearchMenuComponent",
}

registerScreenPlay("ticketGiverPashna", true)

ticketGiverPashnaConvoHandler = CorvetteTicketGiverConvoHandler:new {
 	ticketGiver = ticketGiverPashna
}

PashnaIntelSearchMenuComponent = IntelSearchMenuComponent:new {
	ticketGiver = ticketGiverPashna
}
