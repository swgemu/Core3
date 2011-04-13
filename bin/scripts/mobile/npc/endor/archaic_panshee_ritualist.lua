archaic_panshee_ritualist = Creature:new {
	objectName = "@mob/creature_names:archaic_panshee_ritualist",
	socialGroup = "Panshee Tribe",
	pvpFaction = "Panshee Tribe",
	faction = "",
	level = 60,
	chanceHit = 0.600000,
	damageMin = 445,
	damageMax = 600,
	baseXp = 5738,
	baseHAM = 11000,
	baseHAMmax = 14000,
	armor = 0,
	resists = {25,25,0,0,0,0,0,0,-1},
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
	weapons = {"ewok_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(archaic_panshee_ritualist, "archaic_panshee_ritualist")