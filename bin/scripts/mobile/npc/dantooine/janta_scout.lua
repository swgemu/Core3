janta_scout = Creature:new {
	objectName = "@mob/creature_names:janta_scout",
	socialGroup = "Janta Tribe",
	pvpFaction = "Janta Tribe",
	faction = "",
	level = 51,
	chanceHit = 0.550000,
	damageMin = 420,
	damageMax = 550,
	baseXp = 5007,
	baseHAM = 11000,
	baseHAMmax = 13000,
	armor = 0,
	resists = {-1,35,0,0,0,70,0,0,-1},
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

CreatureTemplates:addCreatureTemplate(janta_scout, "janta_scout")