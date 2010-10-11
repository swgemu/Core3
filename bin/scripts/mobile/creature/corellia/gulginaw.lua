gulginaw = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@monster_name:gulginaw",
	socialGroup = "Gulginaw",
	pvpFaction = "",
	faction = "",
	level = 13,
	chanceHit = 0.290000,
	damageMin = 140,
	damageMax = 150,
	range = 0,
	baseXp = 609,
	baseHAM = 1700,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_avian",
	meatAmount = 75,
	hideType = "hide_",
	hideAmount = 0,
	boneType = "bone_avian",
	boneAmount = 25,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(gulginaw, "gulginaw")
