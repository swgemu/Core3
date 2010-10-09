arachne_drone = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:arachne_drone",
	socialGroup = "Arachne",
	pvpFaction = "",
	faction = "",
	level = 27,
	chanceHit = 0.360000,
	damageMin = 240,
	damageMax = 250,
	range = 25,
	baseXp = 2730,
	baseHAM = 6550,
	armor = 0,
	resists = {35,25,0,40,40,-1,40,-1,-1},
	meatType = "meat_insect",
	meatAmount = 0,
	hideType = "hide_",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0.000000,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"defaultattack",""},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(arachne_drone, "arachne_drone")
