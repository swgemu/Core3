blacklight_pirate_fighter_quest = ShipAgent:new {
	template = "hutt_light_s01_tier3",
	pilotTemplate = "light_fighter_tier3",
	shipType = "fighter",

	experience = 1152,

	lootChance = 0.135,
	lootRolls = 1,
	lootTable = "space_pirate_tier1",

	minCredits = 105,
	maxCredits = 264,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"spynet"},

	color1 = 3,
	color2 = 24,
	texture = 6,
	questLoot = "leader_location",
	appearance = "generic_pirate",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(blacklight_pirate_fighter_quest, "blacklight_pirate_fighter_quest")
