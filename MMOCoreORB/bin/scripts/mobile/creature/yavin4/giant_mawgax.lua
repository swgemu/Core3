giant_mawgax = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:giant_mawgax",
	socialGroup = "Mawgax",
	pvpFaction = "",
	faction = "",
	level = 32,
	chanceHit = 0.400000,
	damageMin = 305,
	damageMax = 320,
	range = 0,
	baseXp = 3188,
	baseHAM = 9550,
	armor = 0,
	resists = {0,30,0,-1,30,-1,0,0,-1},
	meatType = "meat_domesticated",
	meatAmount = 130,
	hideType = "hide_leathery",
	hideAmount = 85,
	boneType = "bone_avian",
	boneAmount = 70,
	milk = 0.000000,
	tamingChance = 0.020000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(giant_mawgax, "giant_mawgax")
