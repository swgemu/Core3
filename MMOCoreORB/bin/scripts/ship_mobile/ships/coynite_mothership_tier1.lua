coynite_mothership_tier1 = ShipAgent:new {
	template = "imperial_gunboat_tier1",
	pilotTemplate = "slow_tier3",
	shipType = "bomber",

	experience = 500,

	lootChance = 0.85,
	lootRolls = 1,
	lootTable = "space_civilian_tier3",

	minCredits = 80,
	maxCredits = 200,

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

ShipAgentTemplates:addShipAgentTemplate(coynite_mothership_tier1, "coynite_mothership_tier1")
