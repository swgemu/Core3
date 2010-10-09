deadly_tanc_mite = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:tanc_mite_eviscerator",
	socialGroup = "Tancmite",
	pvpFaction = "",
	faction = "",
	level = 13,
	chanceHit = 0.290000,
	damageMin = 80,
	damageMax = 90,
	range = 0,
	baseXp = 609,
	baseHAM = 1100,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 4,
	hideType = "hide_",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0.000000,
	tamingChance = 0.050000,
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

CreatureTemplates:addCreatureTemplate(deadly_tanc_mite, "deadly_tanc_mite")
