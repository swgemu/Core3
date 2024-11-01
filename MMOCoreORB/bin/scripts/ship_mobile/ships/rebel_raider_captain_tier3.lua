rebel_raider_captain_tier3 = ShipAgent:new {
	template = "xwing_tier3",
	pilotTemplate = "medium_fighter_tier3",
	shipType = "fighter",

	experience = 1408,

	lootChance = 0.165,
	lootRolls = 1,
	lootTable = "space_rebel_tier3",

	minCredits = 150,
	maxCredits = 323,

	aggressive = 0,

	spaceFaction = "rebel",
	alliedFactions = {"nym", "rebel"},
	enemyFactions = {"imperial", "blacksun", "borvo", "hutt", "pirate", "aynat"},
	imperialFactionReward = 14,
	rebelFactionReward = -28,
	color2 = 3,
	texture = 1,
	questLoot = "yavin_rebel",
	appearance = "rebel_pilot",

	tauntType = "rebel",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(rebel_raider_captain_tier3, "rebel_raider_captain_tier3")
