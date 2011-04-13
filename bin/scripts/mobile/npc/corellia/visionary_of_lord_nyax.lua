visionary_of_lord_nyax = Creature:new {
	objectName = "visionary of Lord Nyax",
	socialGroup = "Lord Nyax",
	pvpFaction = "Lord Nyax",
	faction = "",
	level = 31,
	chanceHit = 0.380000,
	damageMin = 280,
	damageMax = 290,
	baseXp = 3188,
	baseHAM = 8300,
	baseHAMmax = 10100,
	armor = 0,
	resists = {30,45,0,50,-1,-1,50,-1,-1},
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
	weapons = {"ranged_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(visionary_of_lord_nyax, "visionary_of_lord_nyax")