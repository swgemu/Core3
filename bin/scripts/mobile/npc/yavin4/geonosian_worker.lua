geonosian_worker = Creature:new {
	objectName = "@mob/creature_names:geonosian_worker",
	socialGroup = "Geonosian",
	pvpFaction = "Geonosian",
	faction = "",
	level = 44,
	chanceHit = 0.460000,
	damageMin = 360,
	damageMax = 430,
	baseXp = 4279,
	baseHAM = 9700,
	baseHAMmax = 11900,
	armor = 0,
	resists = {25,25,-1,65,0,25,-1,0,-1},
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
	weapons = {"geonosian_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(geonosian_worker, "geonosian_worker")