agrilat_rasp = Creature:new {
	objectName = "@mob/creature_names:agrilat_plumed_rasp",
	socialGroup = "Rasp",
	pvpFaction = "",
	faction = "",
	level = 8,
	chanceHit = 0.270000,
	damageMin = 90,
	damageMax = 110,
	range = 0,
	baseXp = 187,
	baseHAM = 200,
	armor = 0,
	resists = {0,0,0,0,0,10,0,-1,-1},
	meatType = "meat_avian",
	meatAmount = 3,
	hideType = "hide_",
	hideAmount = 0,
	boneType = "bone_avian",
	boneAmount = 2,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = NONE,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(agrilat_rasp, "agrilat_rasp")
