pashnaIntel = {
	itemTemplates = { "object/tangible/loot/dungeon/corellian_corvette/rebel_assassin_filler01.iff", "object/tangible/loot/dungeon/corellian_corvette/rebel_assassin_filler02.iff", "object/tangible/loot/dungeon/corellian_corvette/rebel_assassin_intel.iff" },
}

pashnaTicketInfo = { depPlanet = "corellia", faction = "rebel", missionType = "assassinate" }

pashnaCompensation = { { compType = "faction", faction = "rebel", amount = 100 } }

pashna = { planetName = "corellia", npcTemplate = "corvette_rebel_pashna", x = 6772.57, z = 315, y = -5697.8, direction = 245, cellID = 0, position = STAND }

ticketGiverPashna = CorvetteTicketGiverLogic:new {
	npc = pashna,
	intelMap = pashnaIntel,
	ticketInfo = pashnaTicketInfo,
	giverName = "ticketGiverPashna",
	faction = FACTIONREBEL,
	compensation = pashnaCompensation,
	menuComponent = "PashnaIntelSearchMenuComponent",

	first_location ="@conversation/corvette_pashna_rebel1:s_26d40ca6", --Tell me more about Fort Tusken and why any information would be there.
	second_location = "@conversation/corvette_pashna_rebel1:s_98df29e5", --Tell me more about the Mokk stronghold on Dantooine.
	third_location = "@conversation/corvette_pashna_rebel1:s_2534c3e3", --Tell me more about the Geonosian Bunker.
	go_get_intel = "@conversation/corvette_pashna_rebel1:s_a5591c27", -- I accept this mission.
	hear_locations_quit = "@conversation/corvette_pashna_rebel1:s_36cb0506",--No, maybe another time. Good bye.

	has_intel = "@conversation/corvette_pashna_rebel1:s_aa504b9e",--I think I've found something...
	which_planet = "@conversation/corvette_pashna_rebel1:s_278c1c25",--Not yet. I need more information about the locations I'm to search.
	back_already_reset = "@conversation/corvette_pashna_rebel1:s_1729866a",--I've decided to abort the mission. Please erase all records of my progress.

	bad_intel_1 = "@conversation/corvette_pashna_rebel1:s_8b325a7c", --Show Recall Notice.
	bad_intel_2 = "@conversation/corvette_pashna_rebel1:s_f62f461c", --Show Prisoner Transfer Orders.
	good_intel = "@conversation/corvette_pashna_rebel1:s_bb2081d2", --Show Imperial Dossier.

	go_to_corvette = "@conversation/corvette_pashna_rebel1:s_6992624d",--I am heading to the Corellian corvette. Anything else?
	check_other_places = "@conversation/corvette_pashna_rebel1:s_a128e067",--Looks like I have more to do.
	other_documents = "@conversation/corvette_pashna_rebel1:s_2f26b4c4",--I still have documents for you.

	launch_location = "@conversation/corvette_pashna_rebel1:s_60c4f974", --	Where do I go?
	still_here_decline = "@conversation/corvette_pashna_rebel1:s_32abdf15",--I can't do this anymore. I have to resign from the mission.
}

registerScreenPlay("ticketGiverPashna", true)

ticketGiverPashnaConvoHandler = CorvetteTicketGiverConvoHandler:new {
	ticketGiver = ticketGiverPashna
}

PashnaIntelSearchMenuComponent = CorvetteIntelSearchMenuComponent:new {
	ticketGiver = ticketGiverPashna
}
