specops_trooper = Creature:new {
	objectName = "@mob/creature_names:specops_trooper",
	socialGroup = "rebel",
	pvpFaction = "rebel",
	faction = "rebel",
	level = 17,
	chanceHit = 0.320000,
	damageMin = 160,
	damageMax = 170,
	baseXp = 1102,
	baseHAM = 3500,
	baseHAMmax = 4300,
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
	lootGroups = {},
	weapons = {"imperial_weapons_medium"},
	attacks = merge(riflemanmaster,pistoleermaster,carbineermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(specops_trooper, "specops_trooper")