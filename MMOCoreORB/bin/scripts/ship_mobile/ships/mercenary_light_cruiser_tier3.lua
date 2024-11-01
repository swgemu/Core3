mercenary_light_cruiser_tier3 = ShipAgent:new {
	template = "merchant_cruiser_light_tier3",
	pilotTemplate = "slow_tier3",
	shipType = "bomber",

	experience = 5120,

	lootChance = 0.6,
	lootRolls = 1,
	lootTable = "space_pirate_tier3",

	minCredits = 94,
	maxCredits = 700,

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

ShipAgentTemplates:addShipAgentTemplate(mercenary_light_cruiser_tier3, "mercenary_light_cruiser_tier3")
