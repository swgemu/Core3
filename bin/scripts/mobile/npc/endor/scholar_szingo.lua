scholar_szingo = Creature:new {
	objectName = "@mob/creature_names:scholar_szingo",
	socialGroup = "Marauder",
	pvpFaction = "Marauder",
	faction = "",
	level = 21,
	chanceHit = 0.330000,
	damageMin = 210,
	damageMax = 220,
	baseXp = 1609,
	baseHAM = 5900,
	baseHAMmax = 7200,
	armor = 0,
	resists = {0,0,-1,40,40,-1,-1,-1,-1},
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

CreatureTemplates:addCreatureTemplate(scholar_szingo, "scholar_szingo")