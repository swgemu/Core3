dantooine_miner_scout_tier5 = ShipAgent:new {
	template = "droid_fighter_tier5",
	pilotTemplate = "light_fighter_tier5",
	shipType = "fighter",

	experience = 6710.89,

	lootChance = 0.13,
	lootRolls = 1,
	lootTable = "space_civilian_tier5",

	minCredits = 425,
	maxCredits = 825,

	aggressive = 0,

	spaceFaction = "civilian",
	alliedFactions = {"civilian"},
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(dantooine_miner_scout_tier5, "dantooine_miner_scout_tier5")
