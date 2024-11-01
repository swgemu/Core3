junk_dealer_trader = ShipAgent:new {
	template = "hutt_light_s01_tier3",
	pilotTemplate = "light_fighter_tier3",
	shipType = "fighter",

	experience = 1152,

	lootChance = 0.135,
	lootRolls = 1,
	lootTable = "space_story_dantooine_junk",

	minCredits = 105,
	maxCredits = 264,

	aggressive = 0,

	spaceFaction = "merchant",
	alliedFactions = {"civilian", "rebel", "imperial", "merchant"},
	enemyFactions = {"pirate", "blacksun"},

	color1 = 20,
	color2 = 51,
	texture = 2,
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(junk_dealer_trader, "junk_dealer_trader")
