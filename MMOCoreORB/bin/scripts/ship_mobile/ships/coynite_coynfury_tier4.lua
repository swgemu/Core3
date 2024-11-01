coynite_coynfury_tier4 = ShipAgent:new {
	template = "merchant_cruiser_medium_tier4",
	pilotTemplate = "slow_tier5",
	shipType = "bomber",

	experience = 13107.2,

	lootChance = 0.56,
	lootRolls = 1,
	lootTable = "space_civilian_tier5",

	minCredits = 465,
	maxCredits = 950,

	aggressive = 0,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial"},

	color1 = 5,
	color2 = 42,
	texture = 1,
	appearance = "coynite_officer",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(coynite_coynfury_tier4, "coynite_coynfury_tier4")
