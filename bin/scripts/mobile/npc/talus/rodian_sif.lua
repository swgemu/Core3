rodian_sif = Creature:new {
	objectName = "Rodian Sif",
	socialGroup = "Sif",
	pvpFaction = "Sif",
	faction = "",
	level = 37,
	chanceHit = 0.420000,
	damageMin = 330,
	damageMax = 370,
	baseXp = 3733,
	baseHAM = 9000,
	baseHAMmax = 11000,
	armor = 0,
	resists = {40,40,0,-1,0,-1,-1,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + KILLER + STALKER,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"sif_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(rodian_sif, "rodian_sif")