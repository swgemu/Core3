fath_hray = Creature:new {
	objectName = "@mob/creature_names:fath_hray",
	socialGroup = "Nightsister",
	pvpFaction = "Nightsister",
	faction = "",
	level = 21,
	chanceHit = 0.330000,
	damageMin = 250,
	damageMax = 260,
	baseXp = 1609,
	baseHAM = 2400,
	baseHAMmax = 3000,
	armor = 0,
	resists = {0,0,0,45,45,45,0,-1,-1},
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
	creatureBitmask = NONE,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {""},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(fath_hray, "fath_hray")