dantooine_miner_guard_tier5 = ShipAgent:new {
	template = "z95_tier5",
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

	color1 = 1,
	color2 = 1,
	texture = 5,
	appearance = "civilian",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(dantooine_miner_guard_tier5, "dantooine_miner_guard_tier5")
