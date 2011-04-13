rebel_midshipman = Creature:new {
	objectName = "Rebel Midshipman",
	socialGroup = "Rebel",
	pvpFaction = "Rebel",
	faction = "",
	level = 136,
	chanceHit = 6.250000,
	damageMin = 820,
	damageMax = 1350,
	baseXp = 12895,
	baseHAM = 62000,
	baseHAMmax = 75000,
	armor = 0,
	resists = {50,65,0,0,30,30,80,65,-1},
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
	weapons = {"rebel_weapons_medium"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(rebel_midshipman, "rebel_midshipman")