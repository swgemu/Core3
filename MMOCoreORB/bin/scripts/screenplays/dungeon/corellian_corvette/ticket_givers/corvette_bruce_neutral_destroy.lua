bruceIntel =	{
	itemTemplates = { "object/tangible/loot/dungeon/corellian_corvette/neutral_destroy_filler01.iff", "object/tangible/loot/dungeon/corellian_corvette/neutral_destroy_filler02.iff", "object/tangible/loot/dungeon/corellian_corvette/neutral_destroy_intel.iff" },
}

bruceTicketInfo = { depPlanet = "tatooine", faction = "neutral", missionType = "destroy" }

bruceCompensation = { { compType = "credits", amount = 487 } }

bruce_mcbrain = { planetName = "tatooine", npcTemplate = "corvette_neutral_bruce", x = 7.71, z = 0.2, y = 130.29, direction = 292, cellID = 1177466, position = STAND }

ticketGiverBruce = CorvetteTicketGiverLogic:new {
	npc = bruce_mcbrain,
	intelMap = bruceIntel,
	ticketInfo = bruceTicketInfo,
	giverName = "ticketGiverBruce",
	faction = 0,
	compensation = bruceCompensation,
	menuComponent = "BruceIntelSearchMenuComponent",

	first_location = "@conversation/corvette_bruce_neutral_destroy:s_d6cf9803", -- Okay, what's the first possible location?
	second_location = "@conversation/corvette_bruce_neutral_destroy:s_47a242b", -- Alright, what about the second location?
	third_location = "@conversation/corvette_bruce_neutral_destroy:s_7f2cdc", -- Right, what's the third location?
	go_get_intel = "@conversation/corvette_bruce_neutral_destroy:s_65ecd99d", -- Alright, I will try and find the sequence.
	hear_locations_quit = "@conversation/corvette_bruce_neutral_destroy:s_369d526d",-- Sorry, this sounds like something I can't do right now.

	has_intel = "@conversation/corvette_bruce_neutral_destroy:s_ca5faf1b", --I've found some documents that may be it.
	which_planet = "@conversation/corvette_bruce_neutral_destroy:s_8bd8c49d", -- Could you repeat the information on the locations?
	back_already_reset = "@conversation/corvette_bruce_neutral_destroy:s_283ba480", -- Sorry, I give up, this is taking too long.

	bad_intel_1 = "@conversation/corvette_bruce_neutral_destroy:s_d3f9d91d", -- Not sure about this one, it's 'Bounty Hunter Means and Methods'.
	bad_intel_2 = "@conversation/corvette_bruce_neutral_destroy:s_90650308", --  Maybe this 'The Edict of Jiaan' could be useful?
	good_intel = "@conversation/corvette_bruce_neutral_destroy:s_3e583623", --  Here's a document labeled 'CorSec Destruction Code Sequences'.
	go_to_corvette = "@conversation/corvette_bruce_neutral_destroy:s_77928d48",--Alright, I'll take care of it.

	check_other_places = "@conversation/corvette_bruce_neutral_destroy:s_7e619810",--So I guess I'll have to go and check the other places.
	other_documents = "@conversation/corvette_bruce_neutral_destroy:s_3bfca8b3", -- I was wondering if these other documents would be of use?

	launch_location= "@conversation/corvette_bruce_neutral_destroy:s_2972f7c", --Where was Klaatu again?
	still_here_decline = "@conversation/corvette_bruce_neutral_destroy:s_dc1051b",-- Something came up, can't do it right now.
}

registerScreenPlay("ticketGiverBruce", true)

ticketGiverBruceConvoHandler = CorvetteTicketGiverConvoHandler:new {
	ticketGiver = ticketGiverBruce
}

BruceIntelSearchMenuComponent = CorvetteIntelSearchMenuComponent:new {
	ticketGiver = ticketGiverBruce
}
