janta_rockshaper = Creature:new {
	objectName = "@mob/creature_names:janta_rockshaper",
	socialGroup = "Janta Tribe",
	pvpFaction = "Janta Tribe",
	faction = "",
	level = 75,
	chanceHit = 0.700000,
	damageMin = 495,
	damageMax = 700,
	baseXp = 7115,
	baseHAM = 13000,
	baseHAMmax = 15000,
	armor = 0,
	resists = {100,0,-1,0,0,100,0,-1,-1},
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

CreatureTemplates:addCreatureTemplate(janta_rockshaper, "janta_rockshaper")