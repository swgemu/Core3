event_enhanced_gaping_spider = Creature:new {
	objectName = "@mob/creature_names:geonosian_gaping_spider_fire",
	customName = "Fire Breathing Spider (event)",
	socialGroup = "geonosian_creature",
	pvpFaction = "geonosian_creature",
	faction = "",
	level = 108,
	chanceHit = 2.5,
	damageMin = 715,
	damageMax = 1140,
	baseXp = 0,
	baseHAM = 32000,
	baseHAMmax = 39000,
	armor = 2,
	resists = {50,10,-1,95,-1,10,10,10,-1},
	meatType = "meat_insect",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/gaping_spider.iff"},
	scale = 2.5,
	lootGroups = {},
	weapons = {"creature_spit_small_toxicgreen"},
	conversationTemplate = "",
	attacks = {
		{"strongpoison",""},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(event_enhanced_gaping_spider, "event_enhanced_gaping_spider")
