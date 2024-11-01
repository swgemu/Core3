hutt_assassin_s01_tier3 = ShipAgent:new {
	template = "hutt_medium_s01_tier3",
	pilotTemplate = "light_fighter_tier5",
	shipType = "fighter",

	experience = 1280,

	lootChance = 0.15,
	lootRolls = 1,
	lootTable = "space_hutt_tier3",

	minCredits = 105,
	maxCredits = 264,

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

ShipAgentTemplates:addShipAgentTemplate(hutt_assassin_s01_tier3, "hutt_assassin_s01_tier3")
