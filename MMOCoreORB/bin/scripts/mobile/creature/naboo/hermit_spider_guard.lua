hermit_spider_guard = Creature:new {
	objectName = "@mob/creature_names:hermit_spider_guard",
	socialGroup = "Hermit Spider",
	pvpFaction = "",
	faction = "",
	level = 10,
	chanceHit = 0.270000,
	damageMin = 80,
	damageMax = 90,
	baseXp = 356,
	baseHAM = 750,
	armor = 0,
	resists = {10,10,0,0,0,10,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 9,
	hideType = "hide_",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"},
		{"mildpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(hermit_spider_guard, "hermit_spider_guard")
