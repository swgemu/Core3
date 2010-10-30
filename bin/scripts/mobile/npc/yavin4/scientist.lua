scientist = Creature:new {
	objectName = "@mob/creature_names:scientist",
	socialGroup = "Geonosian",
	pvpFaction = "Geonosian",
	faction = "",
	level = 50,
	chanceHit = 0.510000,
	damageMin = 400,
	damageMax = 510,
	baseXp = 4825,
	baseHAM = 10000,
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
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"rebel_weapons_heavy"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(scientist, "scientist")