kunga_scout = Creature:new {
	objectName = "@mob/creature_names:kunga_scout",
	socialGroup = "Kunga Tribe",
	pvpFaction = "Kunga Tribe",
	faction = "",
	level = 48,
	chanceHit = 0.470000,
	damageMin = 395,
	damageMax = 500,
	baseXp = 4734,
	baseHAM = 10000,
	baseHAMmax = 12000,
	armor = 0,
	resists = {15,35,0,-1,0,60,50,-1,-1},
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

CreatureTemplates:addCreatureTemplate(kunga_scout, "kunga_scout")