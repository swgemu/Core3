kunga_hunter = Creature:new {
	objectName = "@mob/creature_names:kunga_hunter",
	socialGroup = "Kunga Tribe",
	pvpFaction = "Kunga Tribe",
	faction = "",
	level = 37,
	chanceHit = 0.410000,
	damageMin = 340,
	damageMax = 390,
	baseXp = 3733,
	baseHAM = 9200,
	baseHAMmax = 11200,
	armor = 0,
	resists = {0,40,0,-1,-1,80,50,-1,-1},
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

CreatureTemplates:addCreatureTemplate(kunga_hunter, "kunga_hunter")