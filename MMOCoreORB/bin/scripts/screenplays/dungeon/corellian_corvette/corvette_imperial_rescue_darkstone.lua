
darkstoneIntel =	{
			containerIds = { 4105811, 4465384, 4105781 }, -- Lok 3205 -4873, Dantooine -7065 -3326, Yavin4 580 -695
			itemTemplates = { "object/tangible/loot/dungeon/corellian_corvette/neutral_rescue_filler01.iff", "object/tangible/loot/dungeon/corellian_corvette/neutral_rescue_filler02.iff", "object/tangible/loot/dungeon/corellian_corvette/neutral_rescue_intel.iff" },
		}

darkstoneTicketInfo = { depPlanet = "tatooine", faction = "neutral", missionType = "rescue" }

darkstoneCompensation = { { compType = "faction", amount = 100 } }

darkstone = { planetName = "tatooine", npcTemplate = "corvette_imperial_darkstone", x = -5313 , z = 8.4, y = 2662, direction = -175, cellID = 0, position = STAND, mood = "npc_imperial"}

ticketGiverDarkstone = CorvetteTicketGiverLogic:new {
	numberOfActs = 1,
	npc = darkstone,
	intelMap = darkstoneIntel,
	ticketInfo = darkstoneTicketInfo,
	giverName = "ticketGiverDarkstone",
	faction = FACTIONIMPERIAL,
	compensation = darkstoneCompensation,
	badgeNumber = 113,
	menuComponent = "DarkstoneIntelSearchMenuComponent",
}

registerScreenPlay("ticketGiverDarkstone", true)

ticketGiverDarkstoneConvoHandler = CorvetteTicketGiverConvoHandler:new {
	ticketGiver = ticketGiverDarkstone
}

DarkstoneIntelSearchMenuComponent = IntelSearchMenuComponent:new {
	ticketGiver = ticketGiverDarkstone
}