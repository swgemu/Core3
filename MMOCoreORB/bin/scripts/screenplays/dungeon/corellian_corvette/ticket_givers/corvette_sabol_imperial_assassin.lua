sabolIntel =	{
	itemTemplates = { "object/tangible/loot/dungeon/corellian_corvette/imperial_assassin_filler01.iff", "object/tangible/loot/dungeon/corellian_corvette/imperial_assassin_filler02.iff", "object/tangible/loot/dungeon/corellian_corvette/imperial_assassin_intel.iff" },
}

sabolTicketInfo = { depPlanet = "tatooine", faction = "imperial", missionType = "assassinate" }

sabolCompensation = { { compType = "faction", faction = "imperial", amount = 100 } }

lt_sabol = { planetName = "tatooine", npcTemplate = "corvette_imperial_sabol", x = -1291.67, z = 12, y = -3539, direction = 110, cellID = 0, position = STAND, mood = "npc_imperial" }

ticketGiverSabol = CorvetteTicketGiverLogic:new {
	npc = lt_sabol,
	intelMap = sabolIntel,
	ticketInfo = sabolTicketInfo,
	giverName = "ticketGiverSabol",
	faction = FACTIONIMPERIAL,
	compensation = sabolCompensation,
	menuComponent = "sabolIntelSearchMenuComponent",

	first_location = "@conversation/corvette_sabol_imperial1:s_3882c2ff",	--I need more information on Dantooine's Rebel base.
	second_location = "@conversation/corvette_sabol_imperial1:s_930c6037",	--I need more information on the Afarathu Sect on Corellia.
	third_location = "@conversation/corvette_sabol_imperial1:s_62aa89fb",	--I need more information about the Star Tours Tzarina.
	go_get_intel ="@conversation/corvette_sabol_imperial1:s_a5591c27",	--I accept this mission.
	hear_locations_quit = "@conversation/corvette_sabol_imperial1:s_edb0a2f5",	--I can't get myself into this.

	has_intel = "@conversation/corvette_velso_imperial_destroy:s_6e1e63ff", --I believe I found the sequence Sir.
	which_planet = "@conversation/corvette_velso_imperial_destroy:s_9495da35", --What were those locations again?
	back_already_reset = "@conversation/corvette_velso_imperial_destroy:s_a1e2f8b6", --I give up...sir. Please remove all progress I've made from your records.

	bad_intel_1 = "@conversation/corvette_sabol_imperial1:s_3565de4e", --Show the Food Order Form.
	bad_intel_2 = "@conversation/corvette_sabol_imperial1:s_56ede5d3",  --Show the Alliance Transfer Orders.
	good_intel = "@conversation/corvette_sabol_imperial1:s_a0cc7541",--Show the Signed Alliance Transport Document.

	go_to_corvette = "@conversation/corvette_sabol_imperial1:s_d112b46e",--I'm leaving for the Corellian corvette.
	check_other_places = "@conversation/corvette_sabol_imperial1:s_a128e067",--Looks like I have more to do.
	other_documents = "@conversation/corvette_sabol_imperial1:s_2f26b4c4", -- I still have documents for you.

	launch_location =  "@conversation/corvette_sabol_imperial1:s_60c4f974", --Where do I go?
	still_here_decline =  "@conversation/corvette_sabol_imperial1:s_5fd624ee", --I wish to quit this mission. Please erase my progress from your records.
}

registerScreenPlay("ticketGiverSabol", true)

ticketGiverSabolConvoHandler = CorvetteTicketGiverConvoHandler:new {
	ticketGiver = ticketGiverSabol
}

sabolIntelSearchMenuComponent = CorvetteIntelSearchMenuComponent:new {
	ticketGiver = ticketGiverSabol
}
