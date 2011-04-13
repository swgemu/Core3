janta_soothsayer = Creature:new {
	objectName = "@mob/creature_names:janta_soothsayer",
	socialGroup = "Janta Tribe",
	pvpFaction = "Janta Tribe",
	faction = "",
	level = 60,
	chanceHit = 0.650000,
	damageMin = 500,
	damageMax = 710,
	baseXp = 5738,
	baseHAM = 12000,
	baseHAMmax = 14000,
	armor = 0,
	resists = {-1,40,-1,0,0,70,0,-1,-1},
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

CreatureTemplates:addCreatureTemplate(janta_soothsayer, "janta_soothsayer")