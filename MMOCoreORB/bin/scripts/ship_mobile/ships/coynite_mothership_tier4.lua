coynite_mothership_tier4 = ShipAgent:new {
	template = "imperial_gunboat_tier4",
	pilotTemplate = "slow_tier5",
	shipType = "bomber",

	experience = 16384,

	lootChance = 0.7,
	lootRolls = 1,
	lootTable = "space_civilian_tier5",

	minCredits = 500,
	maxCredits = 1000,

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

ShipAgentTemplates:addShipAgentTemplate(coynite_mothership_tier4, "coynite_mothership_tier4")
