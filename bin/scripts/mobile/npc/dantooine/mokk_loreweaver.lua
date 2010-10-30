mokk_loreweaver = Creature:new {
	objectName = "@mob/creature_names:mokk_loreweaver",
	socialGroup = "Mokk Tribe",
	pvpFaction = "Mokk Tribe",
	faction = "",
	level = 47,
	chanceHit = 0.470000,
	damageMin = 370,
	damageMax = 450,
	baseXp = 4643,
	baseHAM = 10000,
	baseHAMmax = 12000,
	armor = 0,
	resists = {15,50,0,-1,-1,60,60,-1,-1},
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

CreatureTemplates:addCreatureTemplate(mokk_loreweaver, "mokk_loreweaver")