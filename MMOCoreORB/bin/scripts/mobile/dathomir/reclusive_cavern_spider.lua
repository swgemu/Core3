reclusive_cavern_spider = Creature:new {
	objectName = "@mob/creature_names:cave_gaping_spider_recluse",
	socialGroup = "spider",
	pvpFaction = "",
	faction = "",
	level = 46,
	chanceHit = 0.46,
	damageMin = 390,
	damageMax = 490,
	baseXp = 4552,
	baseHAM = 11000,
	baseHAMmax = 12000,
	armor = 1,
	resists = {60,60,60,50,20,20,20,20,-1},
	meatType = "meat_insect",
	meatAmount = 41,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 8,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/gaping_spider_recluse.iff"},
	lootGroups = {},
	weapons = {"creature_spit_small_toxicgreen"},
	conversationTemplate = "",
	attacks = {
		{"creatureareaattack",""},
		{"strongpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(reclusive_cavern_spider, "reclusive_cavern_spider")