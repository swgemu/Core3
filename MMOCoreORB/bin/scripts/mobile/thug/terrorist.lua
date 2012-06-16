terrorist = Creature:new {
	objectName = "@mob/creature_names:terrorist",
	socialGroup = "thug",
	pvpFaction = "thug",
	faction = "thug",
	level = 17,
	chanceHit = 0.320000,
	damageMin = 180,
	damageMax = 190,
	baseXp = 1102,
	baseHAM = 2400,
	baseHAMmax = 3000,
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
	creatureBitmask = PACK,
	diet = HERBIVORE,

	aiTemplate = "default",

	templates = {},
	lootGroups = {},
	weapons = {"pirate_weapons_heavy"},
	attacks = merge(riflemanmaster,pistoleermaster,carbineermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(terrorist, "terrorist")