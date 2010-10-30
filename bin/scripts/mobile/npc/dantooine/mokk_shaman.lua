mokk_shaman = Creature:new {
	objectName = "@mob/creature_names:mokk_shaman",
	socialGroup = "Mokk Tribe",
	pvpFaction = "Mokk Tribe",
	faction = "",
	level = 60,
	chanceHit = 0.600000,
	damageMin = 445,
	damageMax = 600,
	baseXp = 5830,
	baseHAM = 11000,
	baseHAMmax = 14000,
	armor = 0,
	resists = {0,60,0,-1,-1,60,60,-1,-1},
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
	creatureBitmask = PACK + KILLER + HERD,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"primitive_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(mokk_shaman, "mokk_shaman")