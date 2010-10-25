chasmal_spider = Creature:new {
	objectName = "@mob/creature_names:gaping_spider_chasmal",
	socialGroup = "Gaping",
	pvpFaction = "",
	faction = "",
	level = 31,
	chanceHit = 0.380000,
	damageMin = 290,
	damageMax = 300,
	range = 0,
	baseXp = 3097,
	baseHAM = 9550,
	armor = 0,
	resists = {30,20,0,0,0,0,10,0,-1},
	meatType = "meat_insect",
	meatAmount = 8,
	hideType = "hide_",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"strongpoison",""},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(chasmal_spider, "chasmal_spider")
