rebel_endscout_tier4 = ShipAgent:new {
	template = "awing_tier4",
	pilotTemplate = "light_fighter_tier4",
	shipType = "fighter",

	experience = 2949.12,

	lootChance = 0.126,
	lootRolls = 1,
	lootTable = "space_rebel_tier5",

	minCredits = 200,
	maxCredits = 500,

	aggressive = 1,

	spaceFaction = "rebel",
	alliedFactions = {"rebel", "merchant", "civilian"},
	enemyFactions = {"imperial", "blacksun", "borvo", "hutt", "pirate", "aynat"},
	imperialFactionReward = 25,
	rebelFactionReward = -49,

	color1 = 59,
	color2 = 59,
	texture = 5,
	questLoot = "rebel_battle_plans",
	appearance = "rebel_pilot",

	tauntType = "rebel",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(rebel_endscout_tier4, "rebel_endscout_tier4")
