tallonIntel = {
	itemTemplates = { "object/tangible/loot/dungeon/corellian_corvette/rebel_rescue_filler01.iff", "object/tangible/loot/dungeon/corellian_corvette/rebel_rescue_filler02.iff", "object/tangible/loot/dungeon/corellian_corvette/rebel_rescue_intel.iff" },
}

tallonTicketInfo = { depPlanet = "corellia", faction = "rebel", missionType = "rescue" }

tallonCompensation = { { compType = "faction", faction = "rebel", amount = 100 } }

tallon = { planetName = "corellia", npcTemplate = "corvette_rebel_adar", x = -5448.03, z = 21, y = -2674.92, direction = 163, cellID = 0, position = STAND }

ticketGiverTallon = CorvetteTicketGiverLogic:new {
	npc = tallon,
	intelMap = tallonIntel,
	ticketInfo = tallonTicketInfo,
	giverName = "ticketGiverTallon",
	faction = FACTIONREBEL,
	compensation = tallonCompensation,
	menuComponent = "tallonIntelSearchMenuComponent",

	first_location = "@conversation/corvette_tallon_rebel1:s_3410977a", --Tell me about the downed Bloodrazor vessel.
	second_location = "@conversation/corvette_tallon_rebel1:s_57214562", --Tell me about the Imperial Prison.
	third_location = "@conversation/corvette_tallon_rebel1:s_151358aa", -- Tell me about the downed Bloodrazor vessel.
	go_get_intel ="@conversation/corvette_tallon_rebel1:s_a5591c27", -- I accept this mission.
	hear_locations_quit = "@conversation/corvette_tallon_rebel1:s_d6695e83",-- No thanks.

	has_intel ="@conversation/corvette_tallon_rebel1:s_4d865d46",--I found several interesting documents and codes.
	which_planet ="@conversation/corvette_tallon_rebel1:s_60c4f974", -- Where do I go?
	back_already_reset = "@conversation/corvette_tallon_rebel1:s_e70aed96", -- I can't continue. Please erase all records of my progress on this mission.

	bad_intel_1 = "@conversation/corvette_tallon_rebel1:s_9b6fd578", --Show the Imperial Resignation Form.
	bad_intel_2 = "@conversation/corvette_tallon_rebel1:s_b0e6356e", --Show the Imperial Purchase Order.
	good_intel = "@conversation/corvette_tallon_rebel1:s_135bf1fb", --Show the Security Override Codes.

	go_to_corvette = "@conversation/corvette_tallon_rebel1:s_67499366",--I am leaving for the Corellian corvette.
	check_other_places = "@conversation/corvette_tallon_rebel1:s_a128e067", --Looks like I have more to do.
	other_documents = "@conversation/corvette_tallon_rebel1:s_2f26b4c4", -- I still have documents for you.

	launch_location ="@conversation/corvette_tallon_rebel1:s_3925fbc0", --I forgot the location of our contact.
	still_here_decline ="@conversation/corvette_tallon_rebel1:s_e70aed96", -- I can't continue. Please erase all records of my progress on this mission.

}

registerScreenPlay("ticketGiverTallon", true)

ticketGiverTallonConvoHandler = CorvetteTicketGiverConvoHandler:new {
	ticketGiver = ticketGiverTallon
}

tallonIntelSearchMenuComponent = CorvetteIntelSearchMenuComponent:new {
	ticketGiver = ticketGiverTallon
}
