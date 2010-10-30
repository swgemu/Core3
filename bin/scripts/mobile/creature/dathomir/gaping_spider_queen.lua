gaping_spider_queen = Creature:new {
	objectName = "@mob/creature_names:gaping_spider_queen",
	socialGroup = "Gaping",
	pvpFaction = "",
	faction = "",
	level = 47,
	chanceHit = 0.440000,
	damageMin = 345,
	damageMax = 400,
	baseXp = 4643,
	baseHAM = 11000,
	baseHAMmax = 11000,
	armor = 0,
	resists = {65,65,40,25,0,-1,0,0,-1},
	meatType = "meat_insect",
	meatAmount = 12,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/gaping_spider_queen.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_toxicgreen"},
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"mediumpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(gaping_spider_queen, "gaping_spider_queen")