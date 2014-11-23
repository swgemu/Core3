cavern_spider_hunter = Creature:new {
	objectName = "@mob/creature_names:gaping_spider_hunter",
	socialGroup = "spider",
	pvpFaction = "",
	faction = "",
	level = 46,
	chanceHit = 0.46,
	damageMin = 390,
	damageMax = 490,
	baseXp = 4552,
	baseHAM = 9500,
	baseHAMmax = 11600,
	armor = 1,
	resists = {140,140,160,115,-1,-1,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 35,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 9,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/gaping_spider_hue.iff"},
	scale = 1.15,
	lootGroups = {},
	weapons = {"creature_spit_small_toxicgreen"},
	conversationTemplate = "",
	attacks = {
		{"mediumpoison",""},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(cavern_spider_hunter, "cavern_spider_hunter")
