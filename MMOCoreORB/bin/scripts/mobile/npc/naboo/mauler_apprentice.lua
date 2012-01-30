mauler_apprentice = Creature:new {
	objectName = "@mob/creature_names:mauler_apprentice",
	socialGroup = "Mauler",
	pvpFaction = "",
	faction = "",
	level = 12,
	chanceHit = 0.290000,
	damageMin = 140,
	damageMax = 150,
	baseXp = 609,
	baseHAM = 810,
	baseHAMmax = 990,
	armor = 0,
	resists = {0,0,10,0,0,0,0,-1,-1},
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
	lootGroups = {},
	weapons = {"pirate_weapons_medium"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(mauler_apprentice, "mauler_apprentice")