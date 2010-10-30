gaping_spider_recluse_queen = Creature:new {
	objectName = "@mob/creature_names:gaping_spider_recluse_queen",
	socialGroup = "Gaping Recluse",
	pvpFaction = "",
	faction = "",
	level = 68,
	chanceHit = 0.650000,
	damageMin = 510,
	damageMax = 730,
	baseXp = 6563,
	baseHAM = 12500,
	baseHAMmax = 12500,
	armor = 0,
	resists = {45,65,45,90,-1,0,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 11,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/gaping_spider_recluse.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_toxicgreen"},
	attacks = {
		{"creatureareapoison",""},
		{"strongpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(gaping_spider_recluse_queen, "gaping_spider_recluse_queen")