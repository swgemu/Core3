erran_sif = Creature:new {
	objectName = "@mob/creature_names:erran_sif",
	socialGroup = "Sif",
	pvpFaction = "Sif",
	faction = "",
	level = 67,
	chanceHit = 0.670000,
	damageMin = 480,
	damageMax = 670,
	baseXp = 6472,
	baseHAM = 12000,
	baseHAMmax = 14000,
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

CreatureTemplates:addCreatureTemplate(erran_sif, "erran_sif")