coynite_communications_vessel_tier4 = ShipAgent:new {
	template = "decimator_tier4",
	pilotTemplate = "heavy_tier4",
	shipType = "bomber",

	experience = 6553.6,

	lootChance = 0.28,
	lootRolls = 1,
	lootTable = "space_civilian_tier4",

	minCredits = 400,
	maxCredits = 800,

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

ShipAgentTemplates:addShipAgentTemplate(coynite_communications_vessel_tier4, "coynite_communications_vessel_tier4")
