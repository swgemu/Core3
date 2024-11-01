rebel_raider_fast_attack_tier3 = ShipAgent:new {
	template = "awing_tier3",
	pilotTemplate = "light_fighter_tier3",
	shipType = "fighter",

	experience = 1152,

	lootChance = 0.135,
	lootRolls = 1,
	lootTable = "space_rebel_tier3",

	minCredits = 105,
	maxCredits = 264,

	aggressive = 0,

	spaceFaction = "rebel",
	alliedFactions = {"nym", "rebel"},
	enemyFactions = {"imperial", "blacksun", "borvo", "hutt", "pirate", "aynat"},
	imperialFactionReward = 12,
	rebelFactionReward = -23,
	color2 = 4,
	texture = 1,
	questLoot = "yavin_rebel",
	appearance = "rebel_pilot",

	tauntType = "rebel_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(rebel_raider_fast_attack_tier3, "rebel_raider_fast_attack_tier3")
