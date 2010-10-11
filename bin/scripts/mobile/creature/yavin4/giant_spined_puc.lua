giant_spined_puc = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:giant_spined_puc",
	socialGroup = "Spined Puc",
	pvpFaction = "",
	faction = "",
	level = 19,
	chanceHit = 0.330000,
	damageMin = 180,
	damageMax = 190,
	range = 0,
	baseXp = 1426,
	baseHAM = 5000,
	armor = 0,
	resists = {10,0,0,-1,-1,-1,-1,-1,-1},
	meatType = "meat_reptilian",
	meatAmount = 7,
	hideType = "hide_leathery",
	hideAmount = 7,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(giant_spined_puc, "giant_spined_puc")
