gaping_spider = Creature:new {
	objectName = "@monster_name:gaping_spider",
	socialGroup = "Gaping",
	pvpFaction = "",
	faction = "",
	level = 26,
	chanceHit = 0.360000,
	damageMin = 250,
	damageMax = 260,
	range = 0,
	baseXp = 2730,
	baseHAM = 8550,
	armor = 0,
	resists = {30,25,-1,0,-1,0,-1,-1,-1},
	meatType = "meat_insect",
	meatAmount = 8,
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
		{"mildpoison",""},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(gaping_spider, "gaping_spider")
