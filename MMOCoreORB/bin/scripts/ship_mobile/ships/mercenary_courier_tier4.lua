mercenary_courier_tier4 = ShipAgent:new {
	template = "hutt_light_s01_tier4",
	pilotTemplate = "light_fighter_tier4",
	shipType = "fighter",

	experience = 2949.12,

	lootChance = 0.126,
	lootRolls = 1,
	lootTable = "space_pirate_tier4",

	minCredits = 200,
	maxCredits = 500,

	aggressive = 0,

	spaceFaction = "civilian",

	color1 = 41,
	color2 = 28,
	texture = 4,
	questLoot = "encrypted_documents",
	appearance = "generic_pirate",

	tauntType = "generic_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(mercenary_courier_tier4, "mercenary_courier_tier4")
