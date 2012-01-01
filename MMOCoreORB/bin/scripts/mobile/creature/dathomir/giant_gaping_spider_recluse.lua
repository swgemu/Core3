giant_gaping_spider_recluse = Creature:new {
	objectName = "@mob/creature_names:giant_gaping_spider_recluse",
	socialGroup = "Gaping Recluse",
	pvpFaction = "",
	faction = "",
	level = 115,
	chanceHit = 3.1,
	damageMin = 775,
	damageMax = 1260,
	baseXp = 10921,
	baseHAM = 33500,
	baseHAMmax = 33500,
	armor = 0,
	resists = {60,60,60,25,0,0,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 11,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/gaping_spider_recluse.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_toxicgreen"},
	conversationTemplate = "",
	attacks = {
		{"creatureareapoison",""},
		{"strongpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(giant_gaping_spider_recluse, "giant_gaping_spider_recluse")