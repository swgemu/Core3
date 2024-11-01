mercenary_light_cruiser_tier5 = ShipAgent:new {
	template = "merchant_cruiser_light_tier5",
	pilotTemplate = "slow_tier5",
	shipType = "bomber",

	experience = 26843.55,

	lootChance = 0.52,
	lootRolls = 1,
	lootTable = "space_pirate_tier5",

	minCredits = 525,
	maxCredits = 1075,

	aggressive = 0,

	spaceFaction = "civilian",

	color1 = 61,
	color2 = 60,
	texture = 4,
	questLoot = "encrypted_documents",
	appearance = "generic_pirate",

	tauntType = "generic_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(mercenary_light_cruiser_tier5, "mercenary_light_cruiser_tier5")
