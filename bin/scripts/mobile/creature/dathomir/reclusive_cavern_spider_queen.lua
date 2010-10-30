reclusive_cavern_spider_queen = Creature:new {
	objectName = "@mob/creature_names:cave_gaping_spider_recluse_queen",
	socialGroup = "Spider Nightsister",
	pvpFaction = "",
	faction = "",
	level = 70,
	chanceHit = 0.650000,
	damageMin = 510,
	damageMax = 730,
	baseXp = 6747,
	baseHAM = 12500,
	baseHAMmax = 12500,
	armor = 0,
	resists = {60,60,60,50,0,0,0,0,-1},
	meatType = "meat_insect",
	meatAmount = 45,
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

CreatureTemplates:addCreatureTemplate(reclusive_cavern_spider_queen, "reclusive_cavern_spider_queen")