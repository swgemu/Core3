revered_panshee_matriarch = Creature:new {
	objectName = "@mob/creature_names:revered_panshee_matriarch",
	socialGroup = "Panshee Tribe",
	pvpFaction = "Panshee Tribe",
	faction = "",
	level = 39,
	chanceHit = 0.430000,
	damageMin = 335,
	damageMax = 380,
	baseXp = 3824,
	baseHAM = 9100,
	baseHAMmax = 11100,
	armor = 0,
	resists = {45,45,0,-1,0,-1,-1,0,-1},
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

CreatureTemplates:addCreatureTemplate(revered_panshee_matriarch, "revered_panshee_matriarch")