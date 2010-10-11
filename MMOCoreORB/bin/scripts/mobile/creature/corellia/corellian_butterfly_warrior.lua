corellian_butterfly_warrior = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "corellian butterfly warrior",
	socialGroup = "Cor. Butterfly",
	pvpFaction = "",
	faction = "",
	level = 14,
	chanceHit = 0.300000,
	damageMin = 170,
	damageMax = 180,
	range = 25,
	baseXp = 714,
	baseHAM = 1300,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 12,
	hideType = "hide_scale",
	hideAmount = 12,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(corellian_butterfly_warrior, "corellian_butterfly_warrior")
