dantooine_miner_guard_tier3 = ShipAgent:new {
	template = "z95_tier3",
	pilotTemplate = "light_fighter_tier3",
	shipType = "fighter",

	experience = 1280,

	lootChance = 0.15,
	lootRolls = 1,
	lootTable = "space_civilian_tier3",

	minCredits = 120,
	maxCredits = 294,

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

ShipAgentTemplates:addShipAgentTemplate(dantooine_miner_guard_tier3, "dantooine_miner_guard_tier3")
