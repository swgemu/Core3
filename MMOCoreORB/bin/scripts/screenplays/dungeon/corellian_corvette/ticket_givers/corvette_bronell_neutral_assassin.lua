bronellIntel =	{
	itemTemplates = { "object/tangible/loot/dungeon/corellian_corvette/neutral_assassin_filler01.iff", "object/tangible/loot/dungeon/corellian_corvette/neutral_assassin_filler02.iff", "object/tangible/loot/dungeon/corellian_corvette/neutral_assassin_intel.iff" },
}

bronellTicketInfo = { depPlanet = "tatooine", faction = "neutral", missionType = "assassinate" }

bronellCompensation = { { compType = "credits", amount = 500 } }

bronell = { planetName = "tatooine", npcTemplate = "corvette_neutral_bronell", x = -6.7, z = 5.8, y = 97.9, direction = 180, cellID = 1177469, position = STAND }

ticketGiverBronell = CorvetteTicketGiverLogic:new {
	npc = bronell,
	intelMap = bronellIntel,
	ticketInfo = bronellTicketInfo,
	giverName = "ticketGiverBronell",
	faction = 0,
	compensation = bronellCompensation,
	menuComponent = "BronellIntelSearchMenuComponent",

	first_location = "@conversation/corvette_bronell_neutral_assassin:s_94bc6e8f", -- Talus, yes? I mean, Talus?
	second_location = "@conversation/corvette_bronell_neutral_assassin:s_2ad476a3", -- Naboo, ok.
	third_location = "@conversation/corvette_bronell_neutral_assassin:s_ba696f5d", -- Lok, yes? Bah, look what you did to me.
	go_get_intel = "@conversation/corvette_bronell_neutral_assassin:s_76e2b2f6", -- Alright, I'll try and get the information we need.
	hear_locations_quit =  "@conversation/corvette_bronell_neutral_assassin:s_12eb211c", -- Yes? Yes! I've had enough, goodbye.

	has_intel = "@conversation/corvette_bronell_neutral_assassin:s_24dbc07d", --I believe so.
	which_planet = "@conversation/corvette_bronell_neutral_assassin:s_9b8c1f57", -- Could you go over the planets and pirates part again?
	back_already_reset = "@conversation/corvette_bronell_neutral_assassin:s_3e2e8616", -- Sorry, I have other things to do. Erase all knowledge of my progress.

	bad_intel_1 = "@conversation/corvette_bronell_neutral_assassin:s_3f04cefb", -- Here, take a look at this Research Request.
	bad_intel_2 = "@conversation/corvette_bronell_neutral_assassin:s_fecfb00f", -- Here, take a look at this Purchase Request Form.
	good_intel = "@conversation/corvette_bronell_neutral_assassin:s_465d7ab2", -- Here, take a look at this Gambling Debt List.

	go_to_corvette = "@conversation/corvette_bronell_neutral_assassin:s_3c2e92a", -- Alright, but how do I get to the corvette?
	check_other_places = "@conversation/corvette_bronell_neutral_assassin:s_c5ae9239", -- On my way to check one of the other hideouts.
	other_documents = "@conversation/corvette_bronell_neutral_assassin:s_d27dcffe", -- I had some other documents I came across."

	launch_location= "@conversation/corvette_bronell_neutral_assassin:s_2972f7c", -- Where was Klaatu again?
	still_here_decline = "@conversation/corvette_bronell_neutral_assassin:s_4a365e4b", -- Sorry, you'll have to find someone else. I cannot continue with this mission.
}

registerScreenPlay("ticketGiverBronell", true)

ticketGiverBronellConvoHandler = CorvetteTicketGiverConvoHandler:new {
	ticketGiver = ticketGiverBronell
}

BronellIntelSearchMenuComponent = CorvetteIntelSearchMenuComponent:new {
	ticketGiver = ticketGiverBronell
}
