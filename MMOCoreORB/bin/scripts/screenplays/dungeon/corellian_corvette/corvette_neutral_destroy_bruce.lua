
bruceIntel =	{
			containerIds = { 3815388, 4305433, 4355495 }, -- Naboo, Corellia, Dathomir
			itemTemplates = { "object/tangible/loot/dungeon/corellian_corvette/neutral_destroy_filler01.iff", "object/tangible/loot/dungeon/corellian_corvette/neutral_destroy_filler02.iff", "object/tangible/loot/dungeon/corellian_corvette/neutral_destroy_intel.iff" },
		}

bruceTicketInfo = { depPlanet = "tatooine", faction = "neutral", missionType = "destroy" }

bruceCompensation = { { compType = "credits", amount = 487 } }

bruce_mcbrain = { planetName = "tatooine", npcTemplate = "corvette_neutral_bruce", x = 7.71, z = 0.2, y = 130.29, direction = 292, cellID = 1177466, position = STAND }

ticketGiverBruce = CorvetteTicketGiverLogic:new {
	numberOfActs = 1,
	npc = bruce_mcbrain,
	intelMap = bruceIntel,
	ticketInfo = bruceTicketInfo,
	giverName = "ticketGiverBruce",
	faction = 0,
	compensation = bruceCompensation,
	badgeNumber = 115,
	menuComponent = "BruceIntelSearchMenuComponent",
}

registerScreenPlay("ticketGiverBruce", true)

ticketGiverBruceConvoHandler = CorvetteTicketGiverConvoHandler:new {
	ticketGiver = ticketGiverBruce
}

BruceIntelSearchMenuComponent = IntelSearchMenuComponent:new {
	ticketGiver = ticketGiverBruce
}
