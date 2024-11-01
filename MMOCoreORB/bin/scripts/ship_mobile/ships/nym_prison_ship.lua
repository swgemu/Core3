nym_prison_ship = ShipAgent:new {
	template = "merchant_cruiser_light_tier1",
	pilotTemplate = "slow_tier1",
	shipType = "bomber",

	experience = 400,

	lootChance = 0.68,
	lootRolls = 1,
	lootTable = "space_nym_tier1",

	minCredits = 60,
	maxCredits = 120,

	aggressive = 0,

	spaceFaction = "nym",
	alliedFactions = {"rebel", "nym"},
	enemyFactions = {"imperial", "merchant", "corsair", "blacksun", "corsec", "rsf"},

	color1 = 59,
	color2 = 20,
	texture = 1,
	appearance = "nym",

	tauntType = "generic_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(nym_prison_ship, "nym_prison_ship")
