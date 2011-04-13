mokk_rockshaper = Creature:new {
	objectName = "@mob/creature_names:mokk_rockshaper",
	socialGroup = "Mokk Tribe",
	pvpFaction = "Mokk Tribe",
	faction = "",
	level = 71,
	chanceHit = 0.650000,
	damageMin = 470,
	damageMax = 650,
	baseXp = 6747,
	baseHAM = 12000,
	baseHAMmax = 14000,
	armor = 0,
	resists = {100,0,100,0,0,100,0,-1,-1},
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

CreatureTemplates:addCreatureTemplate(mokk_rockshaper, "mokk_rockshaper")