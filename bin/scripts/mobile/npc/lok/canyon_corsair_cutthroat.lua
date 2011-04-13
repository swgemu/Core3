canyon_corsair_cutthroat = Creature:new {
	objectName = "@mob/creature_names:canyon_corsair_cutthroat",
	socialGroup = "Corsair",
	pvpFaction = "Corsair",
	faction = "",
	level = 35,
	chanceHit = 0.400000,
	damageMin = 320,
	damageMax = 350,
	baseXp = 3551,
	baseHAM = 8800,
	baseHAMmax = 10800,
	armor = 0,
	resists = {0,45,0,0,-1,0,0,-1,-1},
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

CreatureTemplates:addCreatureTemplate(canyon_corsair_cutthroat, "canyon_corsair_cutthroat")