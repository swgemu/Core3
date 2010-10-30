zealot_of_lord_nyax = Creature:new {
	objectName = "zealot of Lord Nyax",
	socialGroup = "Lord Nyax",
	pvpFaction = "Lord Nyax",
	faction = "",
	level = 25,
	chanceHit = 0.350000,
	damageMin = 250,
	damageMax = 260,
	baseXp = 2637,
	baseHAM = 4100,
	baseHAMmax = 5000,
	armor = 0,
	resists = {0,50,-1,40,-1,-1,40,-1,-1},
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
	weapons = {"pirate_weapons_heavy"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(zealot_of_lord_nyax, "zealot_of_lord_nyax")