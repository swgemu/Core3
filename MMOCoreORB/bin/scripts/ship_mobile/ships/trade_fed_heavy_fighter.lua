trade_fed_heavy_fighter = ShipAgent:new {
	template = "hutt_light_s01_tier2",
	pilotTemplate = "light_fighter_tier3",
	shipType = "fighter",

	experience = 360,

	lootChance = 0.144,
	lootRolls = 1,
	lootTable = "space_trade_fed_tier2",

	minCredits = 65,
	maxCredits = 130,

	aggressive = 0,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"rsf"},

	color1 = 19,
	color2 = 35,
	texture = 3,
	appearance = "trade_fed",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(trade_fed_heavy_fighter, "trade_fed_heavy_fighter")
