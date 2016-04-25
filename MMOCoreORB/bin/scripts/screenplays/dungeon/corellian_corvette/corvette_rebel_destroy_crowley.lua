
crowleyIntel = {
		containerIds = { 4105791, 4355509, 4305433 }, -- Lok -1891 -3032, Dathomir -6308 754, Corellia 5228 1592
		itemTemplates = { "object/tangible/loot/dungeon/corellian_corvette/rebel_destroy_filler01.iff", "object/tangible/loot/dungeon/corellian_corvette/rebel_destroy_filler02.iff", "object/tangible/loot/dungeon/corellian_corvette/rebel_destroy_intel.iff" },
	}

crowleyTicketInfo = { depPlanet = "corellia", faction = "rebel", missionType = "destroy" }

crowleyCompensation = { { compType = "faction", amount = 100 } }

crowley = { planetName = "corellia", npcTemplate = "corvette_rebel_crowley", x = -3404.73, z = 86, y = 3092.64, direction = 323, cellID = 0, position = STAND }

ticketGiverCrowley = CorvetteTicketGiverLogic:new {
	numberOfActs = 1,
	npc = crowley,
	intelMap = crowleyIntel,
	ticketInfo = crowleyTicketInfo,
	giverName = "ticketGiverCrowley",
	faction = FACTIONREBEL,
	compensation = crowleyCompensation,
	badgeNumber = 118,
	menuComponent = "CrowleyIntelSearchMenuComponent",
}

registerScreenPlay("ticketGiverCrowley", true)

ticketGiverCrowleyConvoHandler = CorvetteTicketGiverConvoHandler:new {
  ticketGiver = ticketGiverCrowley
}

CrowleyIntelSearchMenuComponent = IntelSearchMenuComponent:new {
  ticketGiver = ticketGiverCrowley
}
