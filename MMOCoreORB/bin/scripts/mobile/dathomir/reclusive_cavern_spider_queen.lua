reclusive_cavern_spider_queen = Creature:new {
	objectName = "@mob/creature_names:cave_gaping_spider_recluse_queen",
	socialGroup = "spider",
	pvpFaction = "",
	faction = "",
	level = 70,
	chanceHit = 0.65,
	damageMin = 510,
	damageMax = 730,
	baseXp = 6747,
	baseHAM = 11000,
	baseHAMmax = 14000,
	armor = 0,
	resists = {60,60,60,50,30,30,30,30,-1},
	meatType = "meat_insect",
	meatAmount = 45,
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

	aiTemplate = "default",

	templates = {"object/mobile/gaping_spider_recluse.iff"},
	lootGroups = {},
	weapons = {"creature_spit_small_toxicgreen"},
	conversationTemplate = "",
	attacks = {
		{"creatureareapoison",""},
		{"strongpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(reclusive_cavern_spider_queen, "reclusive_cavern_spider_queen")