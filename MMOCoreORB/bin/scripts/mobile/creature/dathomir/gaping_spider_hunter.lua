gaping_spider_hunter = Creature:new {
	objectName = "@mob/creature_names:gaping_spider_hunter",
	socialGroup = "Gaping",
	pvpFaction = "",
	faction = "",
	level = 44,
	chanceHit = 0.460000,
	damageMin = 390,
	damageMax = 490,
	range = 25,
	baseXp = 4370,
	baseHAM = 10550,
	armor = 0,
	resists = {30,30,60,15,-1,-1,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 9,
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
		{"stunattack","stunChance=50"},
		{"strongdisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(gaping_spider_hunter, "gaping_spider_hunter")
