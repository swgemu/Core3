junk_dealer_guardian = ShipAgent:new {
	template = "hutt_heavy_s01_tier3",
	pilotTemplate = "heavy_fighter_tier3",
	shipType = "fighter",

	experience = 1664,

	lootChance = 0.195,
	lootRolls = 1,
	lootTable = "space_story_dantooine_junk",

	minCredits = 170,
	maxCredits = 382,

	aggressive = 0,

	spaceFaction = "merchant",
	alliedFactions = {"civilian", "rebel", "imperial", "merchant"},
	enemyFactions = {"pirate", "blacksun"},

	color1 = 20,
	color2 = 51,
	texture = 2,
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(junk_dealer_guardian, "junk_dealer_guardian")
