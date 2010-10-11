arachne_webmaster = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:arachne_webmaster",
	socialGroup = "Arachne",
	pvpFaction = "",
	faction = "",
	level = 50,
	chanceHit = 0.500000,
	damageMin = 405,
	damageMax = 520,
	range = 0,
	baseXp = 4916,
	baseHAM = 11000,
	armor = 0,
	resists = {35,35,-1,60,60,-1,60,-1,-1},
	meatType = "meat_insect",
	meatAmount = 30,
	hideType = "hide_",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"},
		{"defaultattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(arachne_webmaster, "arachne_webmaster")
