neo_cobral_hitman = Creature:new {
	objectName = "Neo-Cobral hitman",
	socialGroup = "Cobral",
	pvpFaction = "Cobral",
	faction = "",
	level = 21,
	chanceHit = 0.340000,
	damageMin = 220,
	damageMax = 230,
	baseXp = 1803,
	baseHAM = 5400,
	baseHAMmax = 6600,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + STALKER,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"ranged_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(neo_cobral_hitman, "neo_cobral_hitman")