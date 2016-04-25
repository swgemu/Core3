sabolIntel =	{
			containerIds = { 4015461, 4465395, 4355520 }, -- Tatooine 134 -5349, Dantooine -6676 5557,  Dathomir 5696 1952
			itemTemplates = { "object/tangible/loot/dungeon/corellian_corvette/imperial_assassin_filler01.iff", "object/tangible/loot/dungeon/corellian_corvette/imperial_assassin_filler02.iff", "object/tangible/loot/dungeon/corellian_corvette/imperial_assassin_intel.iff" },
		}

sabolTicketInfo = { depPlanet = "tatooine", faction = "imperial", missionType = "assassinate" }

sabolCompensation = { { compType = "credits", amount = 500 } }

lt_sabol = { planetName = "tatooine", npcTemplate = "lt_sabol", x = -1291.67, z = 12, y = -3539, direction = 110, cellID = 0, position = STAND, mood = "npc_imperial" }

ticketGiverSabol = CorvetteTicketGiverLogic:new {
	numberOfActs = 1,
	npc = lt_sabol,
	intelMap = sabolIntel,
	ticketInfo = sabolTicketInfo,
	giverName = "ticketGiverSabol",
	faction = 0,
	compensation = sabolCompensation,
	badgeNumber = 114,
	menuComponent = "sabolIntelSearchMenuComponent",
}

registerScreenPlay("ticketGiverSabol", true)

ticketGiversabolConvoHandler = CorvetteTicketGiverConvoHandler:new {
	ticketGiver = ticketGiverSabol
}

sabolIntelSearchMenuComponent = IntelSearchMenuComponent:new {
	ticketGiver = ticketGiverSabol
}
