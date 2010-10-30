janta_primalist = Creature:new {
	objectName = "@mob/creature_names:janta_primalist",
	socialGroup = "Janta Tribe",
	pvpFaction = "Janta Tribe",
	faction = "",
	level = 42,
	chanceHit = 0.470000,
	damageMin = 405,
	damageMax = 520,
	baseXp = 4097,
	baseHAM = 9700,
	baseHAMmax = 11900,
	armor = 0,
	resists = {-1,0,-1,0,0,60,0,-1,-1},
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
	creatureBitmask = PACK + HERD,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"primitive_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(janta_primalist, "janta_primalist")