imperial_observer = Creature:new {
	objectName = "Imperial observer",
	socialGroup = "self",
	pvpFaction = "self",
	faction = "",
	level = 53,
	chanceHit = 0.540000,
	damageMin = 415,
	damageMax = 540,
	baseXp = 5190,
	baseHAM = 11000,
	baseHAMmax = 13000,
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
	pvpBitmask = ATTACKABLE + AGGRESSIVE,
	creatureBitmask = PACK + KILLER,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"imperial_weapons_heavy"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(imperial_observer, "imperial_observer")