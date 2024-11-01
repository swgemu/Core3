dantooine_miner_guard = ShipAgent:new {
	template = "xwing_tier1",
	pilotTemplate = "medium_fighter_tier1",
	shipType = "fighter",

	experience = 110,

	lootChance = 0.187,
	lootRolls = 1,
	lootTable = "space_civilian_tier1",

	minCredits = 55,
	maxCredits = 110,

	aggressive = 0,

	spaceFaction = "civilian",
	alliedFactions = {"civilian"},

	color1 = 1,
	color2 = 1,
	texture = 5,
	appearance = "civilian",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(dantooine_miner_guard, "dantooine_miner_guard")
