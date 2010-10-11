cave_beetle = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:cave_beetle",
	socialGroup = "Rock Beetle",
	pvpFaction = "",
	faction = "",
	level = 15,
	chanceHit = 0.310000,
	damageMin = 140,
	damageMax = 150,
	range = 25,
	baseXp = 960,
	baseHAM = 3200,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
	meatType = "meat_insect",
	meatAmount = 6,
	hideType = "hide_scale",
	hideAmount = 8,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"mediumpoison",""},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(cave_beetle, "cave_beetle")
