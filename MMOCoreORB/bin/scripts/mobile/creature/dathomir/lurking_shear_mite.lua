lurking_shear_mite = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:lurking_shear_mite",
	socialGroup = "Shearmite",
	pvpFaction = "",
	faction = "",
	level = 15,
	chanceHit = 0.310000,
	damageMin = 160,
	damageMax = 170,
	range = 25,
	baseXp = 831,
	baseHAM = 2700,
	armor = 0,
	resists = {0,10,-1,0,-1,-1,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 15,
	hideType = "hide_",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0.000000,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = STALKER + PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(lurking_shear_mite, "lurking_shear_mite")
