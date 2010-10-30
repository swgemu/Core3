alpha_bolma = Creature:new {
	objectName = "alpha bolma",
	socialGroup = "Bolma",
	pvpFaction = "",
	faction = "",
	level = 33,
	chanceHit = 0.400000,
	damageMin = 315,
	damageMax = 340,
	baseXp = 3279,
	baseHAM = 9600,
	baseHAMmax = 9600,
	armor = 0,
	resists = {45,25,0,-1,0,-1,-1,-1,-1},
	meatType = "meat_wild",
	meatAmount = 500,
	hideType = "hide_leathery",
	hideAmount = 550,
	boneType = "bone_mammal",
	boneAmount = 500,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = HERBIVORE,

	templates = {"object/mobile/alpha_bolma.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(alpha_bolma, "alpha_bolma")