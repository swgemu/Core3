rebel_droid_training_boss = ShipAgent:new {
	template = "z95_tier3",
	pilotTemplate = "light_fighter_tier4",
	shipType = "fighter",

	experience = 1280,

	lootChance = 0.15,
	lootRolls = 1,
	lootTable = "space_rebel_tier3",

	minCredits = 120,
	maxCredits = 294,

	aggressive = 0,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "blacksun", "borvo", "hutt", "aynat"},
	imperialFactionReward = -21,
	rebelFactionReward = 11,

	color1 = 58,
	color2 = 10,
	texture = 3,
	appearance = "generic_pirate",

	tauntType = "generic_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(rebel_droid_training_boss, "rebel_droid_training_boss")
