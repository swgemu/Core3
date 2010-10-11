savage_flewt_queen = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:savage_flewt_queen",
	socialGroup = "Flewt",
	pvpFaction = "",
	faction = "",
	level = 10,
	chanceHit = 0.280000,
	damageMin = 90,
	damageMax = 110,
	range = 0,
	baseXp = 356,
	baseHAM = 900,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_avian",
	meatAmount = 6,
	hideType = "hide_leathery",
	hideAmount = 6,
	boneType = "bone_avian",
	boneAmount = 6,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"},
		{"mildpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(savage_flewt_queen, "savage_flewt_queen")
