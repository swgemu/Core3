crowleyIntel = {
	itemTemplates = { "object/tangible/loot/dungeon/corellian_corvette/rebel_destroy_filler01.iff", "object/tangible/loot/dungeon/corellian_corvette/rebel_destroy_filler02.iff", "object/tangible/loot/dungeon/corellian_corvette/rebel_destroy_intel.iff" },
}

crowleyTicketInfo = { depPlanet = "corellia", faction = "rebel", missionType = "destroy" }

crowleyCompensation = { { compType = "faction", faction = "rebel", amount = 100 } }

crowley = { planetName = "corellia", npcTemplate = "corvette_rebel_crowley", x = -3404.73, z = 86, y = 3092.64, direction = 323, cellID = 0, position = STAND }

ticketGiverCrowley = CorvetteTicketGiverLogic:new {
	npc = crowley,
	intelMap = crowleyIntel,
	ticketInfo = crowleyTicketInfo,
	giverName = "ticketGiverCrowley",
	faction = FACTIONREBEL,
	compensation = crowleyCompensation,
	menuComponent = "CrowleyIntelSearchMenuComponent",

	first_location ="@conversation/corvette_crowley_rebel1:s_c6392194", --Tell me about the Imperial Base.
	second_location = "@conversation/corvette_crowley_rebel1:s_aec5e53e", --Tell me about the Rogue CorSec base on Corellia.
	third_location = "@conversation/corvette_crowley_rebel1:s_eb5ae08", --Tell me about Dathomir Prison.
	go_get_intel = "@conversation/corvette_crowley_rebel1:s_a5591c27", -- I accept this mission.
	hear_locations_quit = "@conversation/corvette_crowley_rebel1:s_74a0348d",--No thanks. I'm not interested in doing this.

	has_intel = "@conversation/corvette_crowley_rebel1:s_b30bd73c",--Yes, I did.
	which_planet = "@conversation/corvette_crowley_rebel1:s_4fa93758",--What am I looking for again?
	back_already_reset = "@conversation/corvette_crowley_rebel1:s_d5084988", --I cannot continue with this mission. Please erase my progress from your records.

	bad_intel_1 ="@conversation/corvette_crowley_rebel1:s_710a8214", --I found this Imperial Memorandum.
	bad_intel_2 ="@conversation/corvette_crowley_rebel1:s_d4a6b26", --I found this Paid Time Off (PTO) Request.
	good_intel ="@conversation/corvette_crowley_rebel1:s_7cfd3686", --I found this Ship Preparation Document.

	go_to_corvette = "@conversation/corvette_crowley_rebel1:s_b0bbc0c3",--I'm off to meet our contact on Corellia.
	check_other_places = "@conversation/corvette_crowley_rebel1:s_a128e067",--Looks like I have more to do.
	other_documents = "@conversation/corvette_crowley_rebel1:s_2f26b4c4",--I still have documents for you.

	launch_location = "@conversation/corvette_crowley_rebel1:s_298e244f", --Where do I go again?
	still_here_decline = "@conversation/corvette_crowley_rebel1:s_d5084988",--I cannot continue with this mission. Please erase my progress from your records.
}

registerScreenPlay("ticketGiverCrowley", true)

ticketGiverCrowleyConvoHandler = CorvetteTicketGiverConvoHandler:new {
	ticketGiver = ticketGiverCrowley
}

CrowleyIntelSearchMenuComponent = CorvetteIntelSearchMenuComponent:new {
	ticketGiver = ticketGiverCrowley
}
