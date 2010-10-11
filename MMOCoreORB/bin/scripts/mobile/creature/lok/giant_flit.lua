giant_flit = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:giant_flit",
	socialGroup = "Flit",
	pvpFaction = "",
	faction = "",
	level = 19,
	chanceHit = 0.320000,
	damageMin = 170,
	damageMax = 180,
	range = 0,
	baseXp = 1426,
	baseHAM = 4550,
	armor = 0,
	resists = {15,0,0,-1,0,0,-1,-1,-1},
	meatType = "meat_avian",
	meatAmount = 11,
	hideType = "hide_",
	hideAmount = 0,
	boneType = "bone_avian",
	boneAmount = 13,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(giant_flit, "giant_flit")
