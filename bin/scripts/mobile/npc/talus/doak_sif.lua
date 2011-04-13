doak_sif = Creature:new {
	objectName = "@mob/creature_names:doak_sif",
	socialGroup = "Sif",
	pvpFaction = "Sif",
	faction = "",
	level = 48,
	chanceHit = 0.490000,
	damageMin = 385,
	damageMax = 480,
	baseXp = 4734,
	baseHAM = 10000,
	baseHAMmax = 12200,
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

CreatureTemplates:addCreatureTemplate(doak_sif, "doak_sif")