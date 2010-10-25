spined_snake_recluse = Creature:new {
	objectName = "@mob/creature_names:spined_snake_recluse",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 14,
	chanceHit = 0.300000,
	damageMin = 160,
	damageMax = 170,
	range = 25,
	baseXp = 609,
	baseHAM = 1100,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_reptilian",
	meatAmount = 11,
	hideType = "hide_leathery",
	hideAmount = 5,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = NONE,
	diet = CARNIVORE,

	templates = {},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"},
		{"mediumpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(spined_snake_recluse, "spined_snake_recluse")
