gaping_spider_recluse = Creature:new {
	objectName = "@mob/creature_names:gaping_spider_recluse",
	socialGroup = "Gaping Recluse",
	pvpFaction = "",
	faction = "",
	level = 44,
	chanceHit = 0.460000,
	damageMin = 390,
	damageMax = 490,
	baseXp = 4370,
	baseHAM = 10550,
	armor = 0,
	resists = {30,30,60,25,-1,-1,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 11,
	hideType = "hide_",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + STALKER + PACK,
	diet = CARNIVORE,

	templates = {},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"mediumpoison",""},
		{"creatureareapoison",""},
		{"strongpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(gaping_spider_recluse, "gaping_spider_recluse")
