lumbering_bolma = Creature:new {
	objectName = "@mob/creature_names:lumbering_bolma",
	socialGroup = "Bolma",
	pvpFaction = "",
	faction = "",
	level = 25,
	chanceHit = 0.360000,
	damageMin = 240,
	damageMax = 250,
	baseXp = 2543,
	baseHAM = 8000,
	baseHAMmax = 8000,
	armor = 0,
	resists = {0,40,0,-1,-1,-1,-1,-1,-1},
	meatType = "meat_wild",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 160,
	boneType = "bone_mammal",
	boneAmount = 150,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/bolma.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(lumbering_bolma, "lumbering_bolma")