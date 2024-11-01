hutt_assassin_s01_tier5 = ShipAgent:new {
	template = "hutt_medium_s01_tier5",
	pilotTemplate = "light_fighter_tier5",
	shipType = "fighter",

	experience = 6710.89,

	lootChance = 0.13,
	lootRolls = 1,
	lootTable = "space_hutt_tier5",

	minCredits = 350,
	maxCredits = 750,

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

ShipAgentTemplates:addShipAgentTemplate(hutt_assassin_s01_tier5, "hutt_assassin_s01_tier5")
