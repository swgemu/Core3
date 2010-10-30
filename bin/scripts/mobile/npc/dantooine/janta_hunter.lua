janta_hunter = Creature:new {
	objectName = "@mob/creature_names:janta_hunter",
	socialGroup = "Janta Tribe",
	pvpFaction = "Janta Tribe",
	faction = "",
	level = 50,
	chanceHit = 0.500000,
	damageMin = 415,
	damageMax = 540,
	baseXp = 4916,
	baseHAM = 11000,
	baseHAMmax = 13000,
	armor = 0,
	resists = {0,0,-1,-1,0,60,-1,-1,-1},
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
	creatureBitmask = PACK + KILLER + HERD,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"primitive_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(janta_hunter, "janta_hunter")