mountain_krevol = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:mountain_krevol",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 15,
	chanceHit = 0.390000,
	damageMin = 150,
	damageMax = 160,
	range = 0,
	baseXp = 831,
	baseHAM = 2200,
	armor = 0,
	resists = {15,5,0,35,0,0,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 3,
	hideType = "hide_scaley",
	hideAmount = 2,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mountain_krevol, "mountain_krevol")
