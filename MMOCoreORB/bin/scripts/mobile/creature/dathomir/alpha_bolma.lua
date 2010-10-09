alpha_bolma = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "alpha bolma",
	socialGroup = "Bolma",
	pvpFaction = "",
	faction = "",
	level = 33,
	chanceHit = 0.400000,
	damageMin = 315,
	damageMax = 340,
	range = 0,
	baseXp = 3279,
	baseHAM = 9600,
	armor = 0,
	resists = {45,25,0,-1,0,-1,-1,-1,-1},
	meatType = "meat_wild",
	meatAmount = 500,
	hideType = "hide_leathery",
	hideAmount = 550,
	boneType = "bone_mammal",
	boneAmount = 500,
	milk = 0.000000,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = PACK + HERD,
	diet = HERBIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(alpha_bolma, "alpha_bolma")
