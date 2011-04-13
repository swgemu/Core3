mauler_master = Creature:new {
	objectName = "@mob/creature_names:mauler_master",
	socialGroup = "Mauler",
	pvpFaction = "",
	faction = "",
	level = 54,
	chanceHit = 0.500000,
	damageMin = 395,
	damageMax = 500,
	baseXp = 5190,
	baseHAM = 10000,
	baseHAMmax = 12000,
	armor = 0,
	resists = {65,35,90,90,90,-1,-1,-1,-1},
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
	creatureBitmask = KILLER,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"pirate_weapons_heavy"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(mauler_master, "mauler_master")