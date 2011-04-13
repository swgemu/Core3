canyon_corsair_destroyer = Creature:new {
	objectName = "@mob/creature_names:canyon_corsair_destroyer",
	socialGroup = "Corsair",
	pvpFaction = "Corsair",
	faction = "",
	level = 40,
	chanceHit = 0.430000,
	damageMin = 355,
	damageMax = 420,
	baseXp = 4006,
	baseHAM = 8800,
	baseHAMmax = 10800,
	armor = 0,
	resists = {0,60,0,0,-1,0,0,-1,-1},
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

CreatureTemplates:addCreatureTemplate(canyon_corsair_destroyer, "canyon_corsair_destroyer")