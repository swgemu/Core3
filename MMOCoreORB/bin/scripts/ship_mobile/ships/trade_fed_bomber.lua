trade_fed_bomber = ShipAgent:new {
	template = "z95_tier2",
	pilotTemplate = "light_fighter_tier3",
	shipType = "bomber",

	experience = 400,

	lootChance = 0.16,
	lootRolls = 1,
	lootTable = "space_trade_fed_tier2",

	minCredits = 70,
	maxCredits = 140,

	aggressive = 0,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"rsf"},

	color1 = 38,
	color2 = 17,
	texture = 4,
	appearance = "trade_fed",

	tauntType = "generic_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(trade_fed_bomber, "trade_fed_bomber")
