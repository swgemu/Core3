bolle_bol = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@monster_name:bolle_bol",
	socialGroup = "Bolle Bol",
	pvpFaction = "",
	faction = "",
	level = 27,
	chanceHit = 0.360000,
	damageMin = 250,
	damageMax = 260,
	range = 0,
	baseXp = 2730,
	baseHAM = 8550,
	armor = 0,
	resists = {25,25,0,-1,40,-1,40,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 450,
	hideType = "hide_leathery",
	hideAmount = 300,
	boneType = "bone_mammal",
	boneAmount = 180,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = HERBIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(bolle_bol, "bolle_bol")
