grassland_blood_marauder = Creature:new {
	objectName = "@mob/creature_names:grassland_blood_marauder",
	socialGroup = "Marauder",
	pvpFaction = "Marauder",
	faction = "",
	level = 50,
	chanceHit = 0.500000,
	damageMin = 420,
	damageMax = 550,
	baseXp = 4916,
	baseHAM = 11000,
	baseHAMmax = 13000,
	armor = 0,
	resists = {30,30,0,-1,-1,-1,0,-1,-1},
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
	weapons = {"pirate_weapons_medium"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(grassland_blood_marauder, "grassland_blood_marauder")