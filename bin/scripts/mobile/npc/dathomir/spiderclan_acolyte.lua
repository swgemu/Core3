spiderclan_acolyte = Creature:new {
	objectName = "Spiderclan acolyte",
	socialGroup = "Sp. Nightsister",
	pvpFaction = "Sp. Nightsister",
	faction = "",
	level = 64,
	chanceHit = 0.500000,
	damageMin = 445,
	damageMax = 600,
	baseXp = 6196,
	baseHAM = 11000,
	baseHAMmax = 14000,
	armor = 0,
	resists = {35,85,100,50,100,100,50,100,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE + AGGRESSIVE,
	creatureBitmask = PACK + KILLER,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"mixed_force_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(spiderclan_acolyte, "spiderclan_acolyte")