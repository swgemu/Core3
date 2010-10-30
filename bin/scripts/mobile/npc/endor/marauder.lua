marauder = Creature:new {
	objectName = "@mob/creature_names:marauder",
	socialGroup = "Marauder",
	pvpFaction = "Marauder",
	faction = "",
	level = 44,
	chanceHit = 0.470000,
	damageMin = 370,
	damageMax = 450,
	baseXp = 4370,
	baseHAM = 9000,
	baseHAMmax = 11900,
	armor = 0,
	resists = {0,0,0,0,-1,-1,0,0,-1},
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
	weapons = {""},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(marauder, "marauder")