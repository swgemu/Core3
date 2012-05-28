slavemaster = Creature:new {
	objectName = "@mob/creature_names:slavemaster",
	socialGroup = "Slaver",
	pvpFaction = "",
	faction = "thug",
	level = 4,
	chanceHit = 0.240000,
	damageMin = 40,
	damageMax = 45,
	baseXp = 62,
	baseHAM = 113,
	baseHAMmax = 138,
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
	creatureBitmask = NONE,
	diet = HERBIVORE,

	templates = {},
	lootGroups = {},
	weapons = {"pirate_weapons_light"},
	attacks = merge(riflemanmaster,pistoleermaster,carbineermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(slavemaster, "slavemaster")