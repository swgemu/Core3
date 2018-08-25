bolle_bol_calf = Creature:new {
	objectName = "@mob/creature_names:bolle_bol_calf",
	socialGroup = "bol",
	faction = "",
	level = 15,
	chanceHit = 0.31,
	damageMin = 160,
	damageMax = 170,
	baseXp = 831,
	baseHAM = 2400,
	baseHAMmax = 3000,
	armor = 0,
	resists = {5,5,5,5,5,5,5,5,-1},
	meatType = "meat_herbivore",
	meatAmount = 350,
	hideType = "hide_leathery",
	hideAmount = 200,
	boneType = "bone_mammal",
	boneAmount = 130,
	milkType = "milk_wild",
	milk = 200,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/bolle_bol_calf.iff"},
	hues = { 0, 1, 2, 3, 4, 5, 6, 7 },
	scale = 0.65,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(bolle_bol_calf, "bolle_bol_calf")
