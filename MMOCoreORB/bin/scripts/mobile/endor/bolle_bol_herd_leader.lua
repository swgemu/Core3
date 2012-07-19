bolle_bol_herd_leader = Creature:new {
	objectName = "@mob/creature_names:bolle_bol_herd_leader",
	socialGroup = "bol",
	pvpFaction = "",
	faction = "",
	level = 35,
	chanceHit = 0.41,
	damageMin = 320,
	damageMax = 350,
	baseXp = 3460,
	baseHAM = 8800,
	baseHAMmax = 10800,
	armor = 0,
	resists = {35,25,25,-1,50,25,50,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 300,
	boneType = "bone_mammal",
	boneAmount = 180,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/bolle_bol_hue.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"knockdownattack","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(bolle_bol_herd_leader, "bolle_bol_herd_leader")