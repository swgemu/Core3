coynite_mothership_tier3 = ShipAgent:new {
	template = "imperial_gunboat_tier3",
	pilotTemplate = "slow_tier4",
	shipType = "bomber",

	experience = 6400,

	lootChance = 0.75,
	lootRolls = 1,
	lootTable = "space_civilian_tier4",

	minCredits = 350,
	maxCredits = 750,

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

ShipAgentTemplates:addShipAgentTemplate(coynite_mothership_tier3, "coynite_mothership_tier3")
