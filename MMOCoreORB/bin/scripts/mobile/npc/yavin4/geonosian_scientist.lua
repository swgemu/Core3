geonosian_scientist = Creature:new {
	objectName = "@mob/creature_names:geonosian_scientist",
	socialGroup = "Geonosian",
	pvpFaction = "Geonosian",
	faction = "",
	level = 48,
	chanceHit = 0.490000,
	damageMin = 385,
	damageMax = 480,
	baseXp = 4643,
	baseHAM = 10000,
	baseHAMmax = 12200,
	armor = 0,
	resists = {15,15,-1,65,0,30,-1,0,-1},
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

	templates = {"object/mobile/shared_dressed_geonosian_scientist_01.iff","object/mobile/shared_dressed_geonosian_scientist_02.iff"},
	lootgroups = {},
	weapons = {"geonosian_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(geonosian_scientist, "geonosian_scientist")