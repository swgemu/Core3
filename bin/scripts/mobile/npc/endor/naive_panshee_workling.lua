naive_panshee_workling = Creature:new {
	objectName = "@mob/creature_names:naive_panshee_workling",
	socialGroup = "Panshee Tribe",
	pvpFaction = "Panshee Tribe",
	faction = "",
	level = 10,
	chanceHit = 0.270000,
	damageMin = 80,
	damageMax = 90,
	baseXp = 356,
	baseHAM = 675,
	baseHAMmax = 825,
	armor = 0,
	resists = {20,20,0,0,0,0,0,-1,-1},
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

CreatureTemplates:addCreatureTemplate(naive_panshee_workling, "naive_panshee_workling")