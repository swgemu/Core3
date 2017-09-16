velsoIntel =	{
	itemTemplates = { "object/tangible/loot/dungeon/corellian_corvette/imperial_destroy_filler01.iff", "object/tangible/loot/dungeon/corellian_corvette/imperial_destroy_filler02.iff", "object/tangible/loot/dungeon/corellian_corvette/imperial_destroy_intel.iff" },
}

velsoTicketInfo = { depPlanet = "naboo", faction = "imperial", missionType = "destroy" }

velsoCompensation = { { compType = "faction", faction = "imperial",  amount = 100 } }

lt_velso = { planetName = "naboo", npcTemplate = "corvette_imperial_velso", x = 23.4, z = .2, y = -19.4, direction = 180, cellID = 1418874, position = STAND, mood = "npc_imperial"}

ticketGiverVelso = CorvetteTicketGiverLogic:new {
	npc = lt_velso,
	intelMap = velsoIntel,
	ticketInfo = velsoTicketInfo,
	giverName = "ticketGiverVelso",
	faction = FACTIONIMPERIAL,
	compensation = velsoCompensation,
	menuComponent = "VelsoIntelSearchMenuComponent",

	first_location = "@conversation/corvette_velso_imperial_destroy:s_1be45010",  --Ok, let me type this down. What's the first lead?
	second_location = "@conversation/corvette_velso_imperial_destroy:s_ed8d835e", --What about the second possibility?
	third_location = "@conversation/corvette_velso_imperial_destroy:s_b1606a2a", --The third option?
	go_get_intel = "@conversation/corvette_velso_imperial_destroy:s_8b2cc767", -- Alright Sir. I will take off at once.
	hear_locations_quit = "@conversation/corvette_velso_imperial_destroy:s_d5fd52c1",--Ok this definitely doesn't sound like my cup of Doxxen tea.

	has_intel = "@conversation/corvette_velso_imperial_destroy:s_6e1e63ff",  --I believe I found the sequence Sir.
	which_planet = "@conversation/corvette_velso_imperial_destroy:s_9495da35", --What were those locations again?
	back_already_reset = "@conversation/corvette_velso_imperial_destroy:s_a1e2f8b6", --I give up...sir. Please remove all progress I've made from your records.

	bad_intel_1 = "@conversation/corvette_velso_imperial_destroy:s_5b38e8f5", --What's this 'Document 56211217.KXYR.170649'?
	bad_intel_2 = "@conversation/corvette_velso_imperial_destroy:s_88da44a4",  --I found this 'Alliance Guide for Safeworld Exploration' , useful perhaps?
	good_intel = "@conversation/corvette_velso_imperial_destroy:s_5dc3f73a",--This 'Ship Destruct Sequence Codes' must be it.

	go_to_corvette = "@conversation/corvette_velso_imperial_destroy:s_566ff600",--Alright so I will be taken to the corvette to blow it up from the inside?
	check_other_places = "@conversation/corvette_velso_imperial_destroy:s_e60ca0aa", --Alright Sir, I'll get back to searching.
	other_documents = "@conversation/corvette_velso_imperial_destroy:s_cd8ede71", --I found some other documents as well.

	launch_location = "@conversation/corvette_velso_imperial_destroy:s_af39813", --I'm sorry Sir, where do I take this ticket again?
	still_here_decline = "@conversation/corvette_velso_imperial_destroy:s_547609c8", --I can't do this. Please remove all progress I've made from your records.
}

registerScreenPlay("ticketGiverVelso", true)

ticketGiverVelsoConvoHandler = CorvetteTicketGiverConvoHandler:new {
	ticketGiver = ticketGiverVelso
}

VelsoIntelSearchMenuComponent = CorvetteIntelSearchMenuComponent:new {
	ticketGiver = ticketGiverVelso
}
