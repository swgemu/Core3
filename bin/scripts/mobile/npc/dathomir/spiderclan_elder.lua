spiderclan_elder = Creature:new {
	objectName = "Spiderclan elder",
	socialGroup = "Sp. Nightsister",
	pvpFaction = "Sp. Nightsister",
	faction = "",
	level = 277,
	chanceHit = 27.250000,
	damageMin = 1520,
	damageMax = 2750,
	baseXp = 26555,
	baseHAM = 321000,
	baseHAMmax = 392000,
	armor = 0,
	resists = {80,100,85,80,100,100,90,100,-1},
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

CreatureTemplates:addCreatureTemplate(spiderclan_elder, "spiderclan_elder")