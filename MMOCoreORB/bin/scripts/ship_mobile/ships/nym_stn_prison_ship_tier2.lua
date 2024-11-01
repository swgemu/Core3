nym_stn_prison_ship_tier2 = ShipAgent:new {
	template = "merchant_cruiser_light_tier2",
	pilotTemplate = "slow_tier3",
	shipType = "bomber",

	experience = 1600,

	lootChance = 0.64,
	lootRolls = 1,
	lootTable = "space_nym_tier3",

	minCredits = 200,
	maxCredits = 480,

	aggressive = 0,

	spaceFaction = "beta_neutral",

	color1 = 59,
	color2 = 20,
	texture = 1,
	appearance = "nym",

	tauntType = "generic_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(nym_stn_prison_ship_tier2, "nym_stn_prison_ship_tier2")
