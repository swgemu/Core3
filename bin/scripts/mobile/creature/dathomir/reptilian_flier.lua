reptilian_flier = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "reptilian flier",
	socialGroup = "Reptilian Flier",
	pvpFaction = "",
	faction = "",
	level = 16,
	chanceHit = 0.310000,
	damageMin = 170,
	damageMax = 180,
	range = 0,
	baseXp = 960,
	baseHAM = 3900,
	armor = 0,
	resists = {5,0,5,0,0,-1,0,-1,-1},
	meatType = "meat_avian",
	meatAmount = 125,
	hideType = "hide_leathery",
	hideAmount = 80,
	boneType = "bone_avian",
	boneAmount = 75,
	milk = 0.000000,
	tamingChance = 0.250000,
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

CreatureTemplates:addCreatureTemplate(reptilian_flier, "reptilian_flier")
