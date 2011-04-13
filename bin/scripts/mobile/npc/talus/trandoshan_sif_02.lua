trandoshan_sif_02 = Creature:new {
	objectName = "Trandoshan Sif 02",
	socialGroup = "Sif",
	pvpFaction = "Sif",
	faction = "",
	level = 43,
	chanceHit = 0.460000,
	damageMin = 360,
	damageMax = 430,
	baseXp = 4279,
	baseHAM = 9500,
	baseHAMmax = 11700,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE + AGGRESSIVE,
	creatureBitmask = PACK + KILLER + STALKER,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"sif_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(trandoshan_sif_02, "trandoshan_sif_02")