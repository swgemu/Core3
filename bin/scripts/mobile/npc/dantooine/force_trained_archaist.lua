force_trained_archaist = Creature:new {
	objectName = "@mob/creature_names:force_trained_archaist",
	socialGroup = "Force Regen.",
	pvpFaction = "",
	faction = "",
	level = 90,
	chanceHit = 0.900000,
	damageMin = 640,
	damageMax = 990,
	baseXp = 8593,
	baseHAM = 13000,
	baseHAMmax = 16000,
	armor = 0,
	resists = {45,45,0,0,0,0,0,0,-1},
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
	creatureBitmask = PACK + KILLER,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"mixed_force_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(force_trained_archaist, "force_trained_archaist")