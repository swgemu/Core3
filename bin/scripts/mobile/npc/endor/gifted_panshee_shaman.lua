gifted_panshee_shaman = Creature:new {
	objectName = "@mob/creature_names:gifted_panshee_shaman",
	socialGroup = "Panshee Tribe",
	pvpFaction = "Panshee Tribe",
	faction = "",
	level = 38,
	chanceHit = 0.420000,
	damageMin = 330,
	damageMax = 370,
	baseXp = 3733,
	baseHAM = 9200,
	baseHAMmax = 11200,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
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

CreatureTemplates:addCreatureTemplate(gifted_panshee_shaman, "gifted_panshee_shaman")