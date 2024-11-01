blacklight_leader_tier2 = ShipAgent:new {
	template = "hutt_light_s02_tier2",
	pilotTemplate = "light_fighter_tier3",
	shipType = "fighter",

	experience = 360,

	lootChance = 0.144,
	lootRolls = 1,
	lootTable = "space_pirate_tier2",

	minCredits = 65,
	maxCredits = 130,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"spynet"},

	color1 = 3,
	color2 = 24,
	texture = 6,
	appearance = "generic_pirate",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(blacklight_leader_tier2, "blacklight_leader_tier2")
