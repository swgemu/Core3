arachne_widow = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:arachne_widow",
	socialGroup = "Arachne",
	pvpFaction = "",
	faction = "",
	level = 58,
	chanceHit = 0.530000,
	damageMin = 400,
	damageMax = 510,
	range = 0,
	baseXp = 5647,
	baseHAM = 12500,
	armor = 0,
	resists = {40,40,0,70,80,0,80,-1,-1},
	meatType = "meat_insect",
	meatAmount = 30,
	hideType = "hide_",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.010000,
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

CreatureTemplates:addCreatureTemplate(arachne_widow, "arachne_widow")
