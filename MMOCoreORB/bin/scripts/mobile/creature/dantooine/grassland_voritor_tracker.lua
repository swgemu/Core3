grassland_voritor_tracker = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:grassland_voritor_tracker",
	socialGroup = "Voritor Lizard",
	pvpFaction = "",
	faction = "",
	level = 45,
	chanceHit = 0.440000,
	damageMin = 375,
	damageMax = 460,
	range = 0,
	baseXp = 4370,
	baseHAM = 9700,
	armor = 0,
	resists = {65,65,0,0,0,0,-1,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 45,
	hideType = "hide_leathery",
	hideAmount = 35,
	boneType = "bone_avian",
	boneAmount = 40,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = STALKER + PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(grassland_voritor_tracker, "grassland_voritor_tracker")
