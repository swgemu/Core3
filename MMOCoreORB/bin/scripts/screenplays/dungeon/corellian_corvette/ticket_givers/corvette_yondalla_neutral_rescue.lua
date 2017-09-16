yondallaIntel =	{
	itemTemplates = { "object/tangible/loot/dungeon/corellian_corvette/neutral_rescue_filler01.iff", "object/tangible/loot/dungeon/corellian_corvette/neutral_rescue_filler02.iff", "object/tangible/loot/dungeon/corellian_corvette/neutral_rescue_intel.iff" },
}

yondallaTicketInfo = { depPlanet = "tatooine", faction = "neutral", missionType = "rescue" }

yondallaCompensation = { { compType = "credits", amount = 500 } }

yondalla = { planetName = "tatooine", npcTemplate = "corvette_neutral_yondalla", x = 20.19, z = -0.89, y = -19.07, direction = 109, cellID = 1134561, position = STAND }

ticketGiverYondalla = CorvetteTicketGiverLogic:new {
	npc = yondalla,
	intelMap = yondallaIntel,
	ticketInfo = yondallaTicketInfo,
	giverName = "ticketGiverYondalla",
	faction = 0,
	compensation = yondallaCompensation,
	menuComponent = "YondallaIntelSearchMenuComponent",

	first_location ="@conversation/corvette_yondalla_neutral_rescue:s_f9acd930", -- Okay what's the first lead?
	second_location ="@conversation/corvette_yondalla_neutral_rescue:s_fa7b5bf6", -- And the second?
	third_location ="@conversation/corvette_yondalla_neutral_rescue:s_7837378f", -- Right, and the third lead?
	go_get_intel ="@conversation/corvette_yondalla_neutral_rescue:s_f7147ad", --Alright, I'll try and find the right papers.
	hear_locations_quit = "@conversation/corvette_yondalla_neutral_rescue:s_3dfd3c32",-- I prefer to stay here on Tatooine, sorry.

	bad_intel_1 = "@conversation/corvette_yondalla_neutral_rescue:s_58879de3", --What about 'A Galaxy Befuddled by A. Rahringt'?
	bad_intel_2 ="@conversation/corvette_yondalla_neutral_rescue:s_2a00185a", --I managed to snatch 'Galactic Phrasebook and Travel Guide'.
	good_intel ="@conversation/corvette_yondalla_neutral_rescue:s_a9be41f8",--This 'CorSec Prisoner Transfer Document' must be it.

	has_intel ="@conversation/corvette_yondalla_neutral_rescue:s_aa693144",--I have retrieved some documents.
	which_planet = "@conversation/corvette_yondalla_neutral_rescue:s_51573633", -- Could you repeat the three leads on how to find the captured assassin?
	back_already_reset ="@conversation/corvette_yondalla_neutral_rescue:s_ec881702", -- I cannot continue. Erase my progress from your records.

	go_to_corvette = "@conversation/corvette_yondalla_neutral_rescue:s_92ca8435",--Alright Klaatu will assist me in intercepting the corvette?
	check_other_places ="@conversation/corvette_yondalla_neutral_rescue:s_6919fb6b",--I will get back to finding it.
	other_documents ="@conversation/corvette_yondalla_neutral_rescue:s_4e2be81c", -- I still have some of the other documents that I found.

	launch_location ="@conversation/corvette_yondalla_neutral_rescue:s_2972f7c", -- Where was Klaatu again?
	still_here_decline = "@conversation/corvette_yondalla_neutral_rescue:s_5dc4acd", -- I've changed my mind. Erase all progress I've made from your records.

}

registerScreenPlay("ticketGiverYondalla", true)

ticketGiverYondallaConvoHandler = CorvetteTicketGiverConvoHandler:new {
	ticketGiver = ticketGiverYondalla
}

YondallaIntelSearchMenuComponent = CorvetteIntelSearchMenuComponent:new {
	ticketGiver = ticketGiverYondalla
}
