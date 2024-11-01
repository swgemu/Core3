coynite_communications_vessel_tier5 = ShipAgent:new {
	template = "decimator_tier5",
	pilotTemplate = "heavy_tier5",
	shipType = "bomber",

	experience = 13421.77,

	lootChance = 0.26,
	lootRolls = 1,
	lootTable = "space_civilian_tier5",

	minCredits = 465,
	maxCredits = 975,

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

ShipAgentTemplates:addShipAgentTemplate(coynite_communications_vessel_tier5, "coynite_communications_vessel_tier5")
