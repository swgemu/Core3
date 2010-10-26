giant_gaping_spider_recluse = Creature:new {
	objectName = "@mob/creature_names:gaping_spider_recluse_giant",
	socialGroup = "Gaping Recluse",
	pvpFaction = "",
	faction = "",
	level = 115,
	chanceHit = 3.100000,
	damageMin = 775,
	damageMax = 1260,
	baseXp = 10921,
	baseHAM = 33500,
	armor = 0,
	resists = {60,60,60,25,0,0,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 11,
	hideType = "hide_",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + STALKER + PACK,
	diet = CARNIVORE,

	templates = {},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"creatureareapoison",""},
		{"strongpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(giant_gaping_spider_recluse, "giant_gaping_spider_recluse")
