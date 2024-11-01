spynet_fighter_tier1 = ShipAgent:new {
	template = "blacksun_light_s04_tier1",
	pilotTemplate = "light_fighter_tier1",
	shipType = "fighter",

	experience = 100,

	lootChance = 0.17,
	lootRolls = 1,
	lootTable = "space_civilian_tier1",

	minCredits = 51,
	maxCredits = 103,

	aggressive = 0,

	spaceFaction = "spynet",
	alliedFactions = {"spynet"},
	enemyFactions = {"imperial", "pirate"},

	color1 = 48,
	color2 = 49,
	texture = 1,
	appearance = "bothan_spynet_pilots",

	tauntType = "generic_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(spynet_fighter_tier1, "spynet_fighter_tier1")
