hutt_quest_hortrix_steelarm_tier3 = ShipAgent:new {
	template = "hutt_medium_s02_tier3",
	pilotTemplate = "medium_fighter_tier4",
	shipType = "fighter",

	experience = 1280,

	lootChance = 1,
	lootRolls = 1,
	lootTable = "space_hortrix_steelarm_quest",

	minCredits = 120,
	maxCredits = 294,

	aggressive = 1,

	spaceFaction = "hutt",
	alliedFactions = {"hutt"},
	enemyFactions = {"blacksun", "valarian", "pirate", "imperial"},

	color1 = 37,
	color2 = 23,
	texture = 3,
	appearance = "hortrix_steelarm",

	tauntType = "hutt",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(hutt_quest_hortrix_steelarm_tier3, "hutt_quest_hortrix_steelarm_tier3")
