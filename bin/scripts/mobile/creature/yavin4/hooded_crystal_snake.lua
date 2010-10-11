hooded_crystal_snake = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:crystal_snake_hooded",
	socialGroup = "Crystal Snake",
	pvpFaction = "",
	faction = "",
	level = 26,
	chanceHit = 0.360000,
	damageMin = 240,
	damageMax = 250,
	range = 25,
	baseXp = 2637,
	baseHAM = 8000,
	armor = 0,
	resists = {20,20,0,0,-1,-1,60,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 5,
	hideType = "hide_scaley",
	hideAmount = 2,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"mediumpoison",""},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(hooded_crystal_snake, "hooded_crystal_snake")
