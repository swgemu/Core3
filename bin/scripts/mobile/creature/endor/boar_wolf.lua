boar_wolf = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@monster_name:boar_wolf",
	socialGroup = "Boar Wolf",
	pvpFaction = "",
	faction = "",
	level = 25,
	chanceHit = 0.360000,
	damageMin = 240,
	damageMax = 250,
	range = 0,
	baseXp = 2543,
	baseHAM = 9000,
	armor = 0,
	resists = {50,-1,30,-1,30,30,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(boar_wolf, "boar_wolf")
