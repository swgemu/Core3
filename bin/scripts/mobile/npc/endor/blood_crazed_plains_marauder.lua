blood_crazed_plains_marauder = Creature:new {
	objectName = "@mob/creature_names:blood_crazed_plains_marauder",
	socialGroup = "Marauder",
	pvpFaction = "Marauder",
	faction = "",
	level = 56,
	chanceHit = 0.550000,
	damageMin = 445,
	damageMax = 600,
	baseXp = 5464,
	baseHAM = 12000,
	baseHAMmax = 15000,
	armor = 0,
	resists = {0,0,0,-1,-1,-1,-1,-1,-1},
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
	creatureBitmask = PACK + KILLER + STALKER,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"pirate_weapons_heavy"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(blood_crazed_plains_marauder, "blood_crazed_plains_marauder")