bolle_bol_stomper = Creature:new {
	objectName = "@mob/creature_names:bolle_bol_stomper",
	socialGroup = "Bolle Bol",
	pvpFaction = "",
	faction = "",
	level = 23,
	chanceHit = 0.340000,
	damageMin = 220,
	damageMax = 230,
	baseXp = 2219,
	baseHAM = 5550,
	baseHAMmax = 5550,
	armor = 0,
	resists = {25,0,-1,-1,50,-1,50,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 0,
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

	templates = {"object/mobile/bolle_bol.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(bolle_bol_stomper, "bolle_bol_stomper")