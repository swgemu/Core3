gaping_spider = Creature:new {
	objectName = "@mob/creature_names:gaping_spider",
	socialGroup = "spider",
	faction = "",
	level = 26,
	chanceHit = 0.36,
	damageMin = 250,
	damageMax = 260,
	baseXp = 2730,
	baseHAM = 7700,
	baseHAMmax = 9400,
	armor = 0,
	resists = {130,125,-1,15,-1,15,-1,-1,-1},
	meatType = "meat_insect",
	meatAmount = 8,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 4,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/gaping_spider.iff"},
	controlDeviceTemplate = "object/intangible/pet/gaping_spider_hue.iff",
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"mildpoison",""},
		{"intimidationattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(gaping_spider, "gaping_spider")
