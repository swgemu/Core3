hutt_assassin_s01_tier1 = ShipAgent:new {
	template = "hutt_medium_s01_tier1",
	pilotTemplate = "light_fighter_tier3",
	shipType = "fighter",

	experience = 100,

	lootChance = 0.17,
	lootRolls = 1,
	lootTable = "space_hutt_tier1",

	minCredits = 51,
	maxCredits = 103,

	aggressive = 1,

	spaceFaction = "jabba",
	alliedFactions = {"jabba"},

	color1 = 37,
	color2 = 23,
	texture = 3,
	appearance = "hutt",

	tauntType = "hutt_assassin",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(hutt_assassin_s01_tier1, "hutt_assassin_s01_tier1")
