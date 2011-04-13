mokk_harvester = Creature:new {
	objectName = "@mob/creature_names:mokk_harvester",
	socialGroup = "Mokk Tribe",
	pvpFaction = "Mokk Tribe",
	faction = "",
	level = 32,
	chanceHit = 0.390000,
	damageMin = 310,
	damageMax = 330,
	baseXp = 3188,
	baseHAM = 8400,
	baseHAMmax = 10200,
	armor = 0,
	resists = {0,40,0,-1,-1,60,60,-1,-1},
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

CreatureTemplates:addCreatureTemplate(mokk_harvester, "mokk_harvester")