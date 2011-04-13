gaping_spider_broodling = Creature:new {
	objectName = "@mob/creature_names:gaping_spider_broodling",
	socialGroup = "Gaping",
	pvpFaction = "",
	faction = "",
	level = 8,
	chanceHit = 0.270000,
	damageMin = 70,
	damageMax = 75,
	baseXp = 235,
	baseHAM = 450,
	baseHAMmax = 450,
	armor = 0,
	resists = {0,0,10,0,0,0,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 5,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/gaping_spider_broodling.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"mildpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(gaping_spider_broodling, "gaping_spider_broodling")