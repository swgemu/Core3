bolle_bol_female = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:bolle_bol_female",
	socialGroup = "Bolle Bol",
	pvpFaction = "",
	faction = "",
	level = 32,
	chanceHit = 0.390000,
	damageMin = 290,
	damageMax = 300,
	range = 0,
	baseXp = 3188,
	baseHAM = 9800,
	armor = 0,
	resists = {0,0,0,0,50,0,50,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 300,
	boneType = "bone_mammal",
	boneAmount = 180,
	milk = 0.000000,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = HERBIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(bolle_bol_female, "bolle_bol_female")
