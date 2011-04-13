bolle_bol_herd_leader = Creature:new {
	objectName = "@mob/creature_names:bolle_bol_herd_leader",
	socialGroup = "Bolle Bol",
	pvpFaction = "",
	faction = "",
	level = 35,
	chanceHit = 0.410000,
	damageMin = 320,
	damageMax = 350,
	baseXp = 3460,
	baseHAM = 9800,
	baseHAMmax = 9800,
	armor = 0,
	resists = {35,0,0,-1,50,0,50,-1,-1},
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
		{"knockdownattack","knockdownChance=50"},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(bolle_bol_herd_leader, "bolle_bol_herd_leader")