blacklight_assassin_tier4 = ShipAgent:new {
	template = "hutt_light_s02_tier4",
	pilotTemplate = "light_fighter_tier4",
	shipType = "fighter",

	experience = 2949.12,

	lootChance = 0.126,
	lootRolls = 1,
	lootTable = "space_pirate_tier4",

	minCredits = 200,
	maxCredits = 500,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"spynet"},

	color1 = 3,
	color2 = 3,
	texture = 6,
	appearance = "generic_pirate",

	tauntType = "generic_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(blacklight_assassin_tier4, "blacklight_assassin_tier4")
