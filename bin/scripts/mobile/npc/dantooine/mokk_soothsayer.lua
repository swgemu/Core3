mokk_soothsayer = Creature:new {
	objectName = "@mob/creature_names:mokk_soothsayer",
	socialGroup = "Mokk Tribe",
	pvpFaction = "Mokk Tribe",
	faction = "",
	level = 43,
	chanceHit = 0.440000,
	damageMin = 365,
	damageMax = 440,
	baseXp = 4188,
	baseHAM = 93000,
	baseHAMmax = 113000,
	armor = 0,
	resists = {40,60,0,-1,-1,60,60,-1,-1},
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
	creatureBitmask = PACK + HERD,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"primitive_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(mokk_soothsayer, "mokk_soothsayer")