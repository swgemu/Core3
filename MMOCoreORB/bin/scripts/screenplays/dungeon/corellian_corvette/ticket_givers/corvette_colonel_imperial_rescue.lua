darkstoneIntel =	{
	itemTemplates = { "object/tangible/loot/dungeon/corellian_corvette/imperial_rescue_filler01.iff", "object/tangible/loot/dungeon/corellian_corvette/imperial_rescue_filler02.iff", "object/tangible/loot/dungeon/corellian_corvette/imperial_rescue_intel.iff" },
}

darkstoneTicketInfo = { depPlanet = "naboo", faction = "imperial", missionType = "rescue" }

darkstoneCompensation = { { compType = "faction", faction = "imperial",  amount = 100 } }

darkstone = { planetName = "tatooine", npcTemplate = "corvette_imperial_darkstone", x = -5313 , z = 8.4, y = 2662, direction = -175, cellID = 0, position = STAND, mood = "npc_imperial"}

ticketGiverDarkstone = CorvetteTicketGiverLogic:new {
	npc = darkstone,
	intelMap = darkstoneIntel,
	ticketInfo = darkstoneTicketInfo,
	giverName = "ticketGiverDarkstone",
	faction = FACTIONIMPERIAL,
	compensation = darkstoneCompensation,
	menuComponent = "DarkstoneIntelSearchMenuComponent",

	first_location = "@conversation/corvette_colonel_imperial1:s_458f152b",	--I need more information on the Woolamander Palace.
	second_location = "@conversation/corvette_colonel_imperial1:s_41506e32",--I need more information on the Rogue CorSec base.
	third_location = "@conversation/corvette_colonel_imperial1:s_f2177029",	--I need more information on the Droid Engineer cave.
	go_get_intel = "@conversation/corvette_colonel_imperial1:s_a5591c27",	--I accept this mission.
	hear_locations_quit = "@conversation/corvette_colonel_imperial1:s_2a8874c3",--Then again, I'd rather not help. Sorry.

	has_intel = "@conversation/corvette_colonel_imperial1:s_1b0601e4", --I think I've found what you're looking for.
	which_planet = "@conversation/corvette_colonel_imperial1:s_4fd6735c", --I need more information about this ordeal.
	back_already_reset = "@conversation/corvette_colonel_imperial1:s_5dad02b", --I don't want to do this anymore. Find someone else and erase all records of my progress.

	bad_intel_1 = "@conversation/corvette_colonel_imperial1:s_c2f40cdd", --Show the Purchase Order Form.
	bad_intel_2 = "@conversation/corvette_colonel_imperial1:s_e6ef1e0c",  --Show the Research Request.
	good_intel = "@conversation/corvette_colonel_imperial1:s_5bc1d51e",--Show the Prisoner Transport Order.

	go_to_corvette = "@conversation/corvette_colonel_imperial1:s_61a71fef",--I'm taking my leave to board the corvette.
	check_other_places = "@conversation/corvette_colonel_imperial1:s_a128e067",--Looks like I have more to do.
	other_documents = "@conversation/corvette_colonel_imperial1:s_2f26b4c4", --I still have documents for you.

	launch_location =  "@conversation/corvette_colonel_imperial1:s_60c4f974", --Where do I go?
	still_here_decline =  "@conversation/corvette_colonel_imperial1:s_d5ab67dd", --I don't want to do this anymore. Erase all records of my progress.
}

registerScreenPlay("ticketGiverDarkstone", true)

ticketGiverDarkstoneConvoHandler = CorvetteTicketGiverConvoHandler:new {
	ticketGiver = ticketGiverDarkstone
}

DarkstoneIntelSearchMenuComponent = CorvetteIntelSearchMenuComponent:new {
	ticketGiver = ticketGiverDarkstone
}
