spynet_operative_bomber = ShipAgent:new {
	template = "blacksun_medium_s01_tier3",
	pilotTemplate = "medium_fighter_tier1",
	shipType = "bomber",

	experience = 1408,

	lootChance = 0.165,
	lootRolls = 1,
	lootTable = "space_civilian_tier1",

	minCredits = 150,
	maxCredits = 323,

	aggressive = 0,

	spaceFaction = "spynet",
	alliedFactions = {"spynet"},
	enemyFactions = {"imperial", "pirate"},

	color1 = 48,
	color2 = 49,
	texture = 1,
	appearance = "bothan_spynet_pilots",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(spynet_operative_bomber, "spynet_operative_bomber")
