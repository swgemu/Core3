coynite_communications_vessel_tier1 = ShipAgent:new {
	template = "decimator_tier1",
	pilotTemplate = "heavy_tier1",
	shipType = "bomber",

	experience = 200,

	lootChance = 0.34,
	lootRolls = 1,
	lootTable = "space_civilian_tier1",

	minCredits = 60,
	maxCredits = 120,

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

ShipAgentTemplates:addShipAgentTemplate(coynite_communications_vessel_tier1, "coynite_communications_vessel_tier1")
