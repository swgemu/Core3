boar_wolf_cub = Creature:new {
	objectName = "@mob/creature_names:boar_wolf_cub",
	socialGroup = "boar",
	faction = "",
	level = 18,
	chanceHit = 0.32,
	damageMin = 160,
	damageMax = 170,
	baseXp = 1257,
	baseHAM = 3500,
	baseHAMmax = 4300,
	armor = 0,
	resists = {115,5,110,5,5,5,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 45,
	hideType = "hide_leathery",
	hideAmount = 35,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 1,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/boar_wolf_cub.iff"},
	hues = { 24, 25, 26, 27, 28, 29, 30, 31 },
	scale = 0.75,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(boar_wolf_cub, "boar_wolf_cub")
