coynite_mothership_tier5 = ShipAgent:new {
	template = "imperial_gunboat_tier5",
	pilotTemplate = "slow_tier5",
	shipType = "bomber",

	experience = 33554.43,

	lootChance = 0.65,
	lootRolls = 1,
	lootTable = "space_civilian_tier5",

	minCredits = 617,
	maxCredits = 1100,

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

ShipAgentTemplates:addShipAgentTemplate(coynite_mothership_tier5, "coynite_mothership_tier5")
