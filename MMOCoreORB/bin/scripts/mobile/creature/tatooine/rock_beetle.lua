rock_beetle = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:rock_beetle",
	socialGroup = "Rock Beetle",
	pvpFaction = "",
	faction = "",
	level = 14,
	chanceHit = 0.300000,
	damageMin = 140,
	damageMax = 150,
	range = 25,
	baseXp = 714,
	baseHAM = 2200,
	armor = 0,
	resists = {25,0,0,0,0,0,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 6,
	hideType = "hide_scaley",
	hideAmount = 6,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
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

CreatureTemplates:addCreatureTemplate(rock_beetle, "rock_beetle")
