endor_trader_mercenary = ShipAgent:new {
	template = "z95_tier4",
	pilotTemplate = "light_fighter_tier4",
	shipType = "fighter",

	experience = 3276.8,

	lootChance = 0.14,
	lootRolls = 1,
	lootTable = "space_merchant_tier4",

	minCredits = 225,
	maxCredits = 525,

	aggressive = 0,

	spaceFaction = "merchant",
	alliedFactions = {"civilian", "rebel", "imperial", "merchant"},
	enemyFactions = {"hutt", "pirate", "blacksun"},

	color1 = 39,
	color2 = 13,
	texture = 4,
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(endor_trader_mercenary, "endor_trader_mercenary")
