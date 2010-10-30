novice_force_mystic = Creature:new {
	objectName = "@mob/creature_names:novice_force_mystic",
	socialGroup = "Force Reneg.",
	pvpFaction = "",
	faction = "",
	level = 60,
	chanceHit = 0.600000,
	damageMin = 475,
	damageMax = 660,
	baseXp = 5830,
	baseHAM = 1100,
	baseHAMmax = 1300,
	armor = 0,
	resists = {30,30,0,0,0,0,0,0,-1},
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

CreatureTemplates:addCreatureTemplate(novice_force_mystic, "novice_force_mystic")