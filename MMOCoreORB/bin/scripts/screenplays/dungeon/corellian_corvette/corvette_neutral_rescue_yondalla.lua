
yondallaIntel =	{
			containerIds = { 3795387, 4395565, 4005742 }, -- Talus, Rori, Endor
			itemTemplates = { "object/tangible/loot/dungeon/corellian_corvette/neutral_rescue_filler01.iff", "object/tangible/loot/dungeon/corellian_corvette/neutral_rescue_filler02.iff", "object/tangible/loot/dungeon/corellian_corvette/neutral_rescue_intel.iff" },
		}

yondallaTicketInfo = { depPlanet = "tatooine", faction = "neutral", missionType = "rescue" }

yondallaCompensation = { { compType = "credits", amount = 500 } }

yondalla = { planetName = "tatooine", npcTemplate = "yondalla", x = 20.19, z = -0.89, y = -19.07, direction = 109, cellID = 1134561, position = STAND }

ticketGiverYondalla = CorvetteTicketGiverLogic:new {
	numberOfActs = 1,
	npc = yondalla,
	intelMap = yondallaIntel,
	ticketInfo = yondallaTicketInfo,
	giverName = "ticketGiverYondalla",
	faction = 0,
	compensation = yondallaCompensation,
	badgeNumber = 116,
	menuComponent = "YondallaIntelSearchMenuComponent",
}

registerScreenPlay("ticketGiverYondalla", true)

ticketGiverYondallaConvoHandler = CorvetteTicketGiverConvoHandler:new {
	ticketGiver = ticketGiverYondalla
}

YondallaIntelSearchMenuComponent = IntelSearchMenuComponent:new {
	ticketGiver = ticketGiverYondalla
}
