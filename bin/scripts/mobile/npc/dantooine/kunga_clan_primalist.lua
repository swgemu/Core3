kunga_clan_primalist = Creature:new {
	objectName = "@mob/creature_names:kunga_clan_primalist",
	socialGroup = "Kunga Tribe",
	pvpFaction = "Kunga Tribe",
	faction = "",
	level = 40,
	chanceHit = 0.420000,
	damageMin = 360,
	damageMax = 430,
	baseXp = 3915,
	baseHAM = 9000,
	baseHAMmax = 11000,
	armor = 0,
	resists = {0,60,0,-1,-1,60,50,-1,-1},
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

CreatureTemplates:addCreatureTemplate(kunga_clan_primalist, "kunga_clan_primalist")