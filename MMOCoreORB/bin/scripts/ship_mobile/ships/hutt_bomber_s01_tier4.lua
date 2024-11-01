hutt_bomber_s01_tier4 = ShipAgent:new {
	template = "hutt_heavy_s01_tier4",
	pilotTemplate = "heavy_fighter_tier4",
	shipType = "bomber",

	experience = 4259.84,

	lootChance = 0.182,
	lootRolls = 1,
	lootTable = "space_hutt_tier4",

	minCredits = 280,
	maxCredits = 650,

	aggressive = 1,

	spaceFaction = "hutt",
	alliedFactions = {"hutt"},
	enemyFactions = {"blacksun", "valarian", "pirate", "imperial"},

	color1 = 37,
	color2 = 23,
	texture = 3,
	appearance = "hutt",

	tauntType = "hutt",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(hutt_bomber_s01_tier4, "hutt_bomber_s01_tier4")
