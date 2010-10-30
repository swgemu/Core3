janta_shaman = Creature:new {
	objectName = "@mob/creature_names:janta_shaman",
	socialGroup = "Janta Tribe",
	pvpFaction = "Janta Tribe",
	faction = "",
	level = 60,
	chanceHit = 0.650000,
	damageMin = 470,
	damageMax = 650,
	baseXp = 5830,
	baseHAM = 12000,
	baseHAMmax = 14000,
	armor = 0,
	resists = {-1,40,-1,0,100,100,0,-1,-1},
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

CreatureTemplates:addCreatureTemplate(janta_shaman, "janta_shaman")