kunga_shaman = Creature:new {
	objectName = "@mob/creature_names:kunga_shaman",
	socialGroup = "Kunga Tribe",
	pvpFaction = "Kunga Tribe",
	faction = "",
	level = 57,
	chanceHit = 0.550000,
	damageMin = 450,
	damageMax = 610,
	baseXp = 5555,
	baseHAM = 11000,
	baseHAMmax = 14000,
	armor = 0,
	resists = {0,0,0,40,40,-1,-1,0,-1},
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

CreatureTemplates:addCreatureTemplate(kunga_shaman, "kunga_shaman")