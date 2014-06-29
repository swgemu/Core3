gaping_spider_broodling = Creature:new {
	objectName = "@mob/creature_names:gaping_spider_broodling",
	socialGroup = "spider",
	pvpFaction = "",
	faction = "",
	level = 8,
	chanceHit = 0.27,
	damageMin = 70,
	damageMax = 75,
	baseXp = 235,
	baseHAM = 405,
	baseHAMmax = 495,
	armor = 0,
	resists = {0,0,10,0,0,0,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 5,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 5,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + STALKER + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/gaping_spider_broodling.iff"},
	scale = 0.75,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"mildpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(gaping_spider_broodling, "gaping_spider_broodling")
