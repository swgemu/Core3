enhanced_gaping_spider = Creature:new {
	objectName = "@mob/creature_names:enhanced_gaping_spider",
	socialGroup = "Geon. Monster",
	pvpFaction = "",
	faction = "",
	level = 108,
	chanceHit = 2.5,
	damageMin = 715,
	damageMax = 1140,
	baseXp = 10267,
	baseHAM = 3200,
	baseHAMmax = 3900,
	armor = 0,
	resists = {50,20,-1,95,-1,20,20,20,-1},
	meatType = "meat_insect",
	meatAmount = 50,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/gaping_spider.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_toxicgreen"},
	conversationTemplate = "",
	attacks = {
		{"strongpoison",""},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(enhanced_gaping_spider, "enhanced_gaping_spider")