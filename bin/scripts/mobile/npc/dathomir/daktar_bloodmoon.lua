daktar_bloodmoon = Creature:new {
	objectName = "@mob/creature_names:daktar_bloodmoon",
	socialGroup = "Sith Shadow",
	pvpFaction = "Sith Shadow",
	faction = "",
	level = 115,
	chanceHit = 1.000000,
	damageMin = 820,
	damageMax = 1350,
	baseXp = 10921,
	baseHAM = 24500,
	baseHAMmax = 30000,
	armor = 0,
	resists = {80,80,80,80,80,80,80,80,-1},
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
	creatureBitmask = PACK + KILLER,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"pirate_weapons_heavy"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(daktar_bloodmoon, "daktar_bloodmoon")