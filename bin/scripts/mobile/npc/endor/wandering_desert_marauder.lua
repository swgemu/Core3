wandering_desert_marauder = Creature:new {
	objectName = "@mob/creature_names:wandering_desert_marauder",
	socialGroup = "Marauder",
	pvpFaction = "Marauder",
	faction = "",
	level = 47,
	chanceHit = 0.490000,
	damageMin = 385,
	damageMax = 480,
	baseXp = 4643,
	baseHAM = 10000,
	baseHAMmax = 12200,
	armor = 0,
	resists = {25,20,0,0,-1,0,0,-1,-1},
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
	weapons = {""},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(wandering_desert_marauder, "wandering_desert_marauder")