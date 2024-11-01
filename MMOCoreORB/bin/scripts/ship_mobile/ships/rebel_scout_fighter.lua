rebel_scout_fighter = ShipAgent:new {
	template = "awing_tier1",
	pilotTemplate = "light_fighter_tier1",
	shipType = "fighter",

	experience = 90,

	lootChance = 0.153,
	lootRolls = 1,
	lootTable = "space_rebel_tier1",

	minCredits = 51,
	maxCredits = 103,

	aggressive = 0,

	spaceFaction = "rebel",
	alliedFactions = {"rebel", "merchant", "civilian"},
	enemyFactions = {"imperial", "blacksun", "borvo", "hutt", "pirate", "aynat"},
	imperialFactionReward = 2,
	rebelFactionReward = -3,

	color1 = 59,
	color2 = 59,
	texture = 5,
	questLoot = "encrypted_rebel_data",
	appearance = "rebel_pilot",

	tauntType = "rebel_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(rebel_scout_fighter, "rebel_scout_fighter")
