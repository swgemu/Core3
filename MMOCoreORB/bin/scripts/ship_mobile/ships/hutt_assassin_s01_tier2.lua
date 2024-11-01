hutt_assassin_s01_tier2 = ShipAgent:new {
	template = "hutt_medium_s01_tier2",
	pilotTemplate = "light_fighter_tier4",
	shipType = "fighter",

	experience = 400,

	lootChance = 0.16,
	lootRolls = 1,
	lootTable = "space_hutt_tier2",

	minCredits = 65,
	maxCredits = 130,

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

ShipAgentTemplates:addShipAgentTemplate(hutt_assassin_s01_tier2, "hutt_assassin_s01_tier2")
