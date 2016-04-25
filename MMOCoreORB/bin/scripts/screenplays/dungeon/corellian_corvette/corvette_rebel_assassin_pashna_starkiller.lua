
starkillerIntel = {
	containerIds = { 4245460, 4015451, 4305478 }, -- yavin4 -6332 -476 ,tatooine -3978 6259, corellia 1353 -329
	itemTemplates = { "object/tangible/loot/dungeon/corellian_corvette/rebel_assassin_filler01.iff", "object/tangible/loot/dungeon/corellian_corvette/rebel_assassin_filler02.iff", "object/tangible/loot/dungeon/corellian_corvette/rebel_assassin_intel.iff" },
}

starkillerTicketInfo = { depPlanet = "corellia", faction = "rebel", missionType = "assassinate" }

starkillerCompensation = { { compType = "credits", amount = 500 } }

starkiller = { planetName = "corellia", npcTemplate = "pashna", x = 6772.57, z = 315, y = -5697.8, direction = 245, cellID = 0, position = STAND }

ticketGiverStarkiller = CorvetteTicketGiverLogic:new {
	numberOfActs = 1,
	npc = starkiller,
	intelMap = starkillerIntel,
	ticketInfo = starkillerTicketInfo,
	giverName = "ticketGiverStarkiller",
	faction = 0,
	compensation = starkillerCompensation,
	badgeNumber = 120,
	menuComponent = "StarkillerIntelSearchMenuComponent",
}

registerScreenPlay("ticketGiverStarkiller", true)

ticketGiverStarkillerConvoHandler = CorvetteTicketGiverConvoHandler:new {
 	ticketGiver = ticketGiverStarkiller
}

StarkillerIntelSearchMenuComponent = IntelSearchMenuComponent:new {
	ticketGiver = ticketGiverStarkiller
}
