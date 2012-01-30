mauler_master = Creature:new {
	objectName = "@mob/creature_names:mauler_master",
	socialGroup = "Mauler",
	pvpFaction = "",
	faction = "",
	level = 54,
	chanceHit = 0.5,
	damageMin = 395,
	damageMax = 500,
	baseXp = 5190,
	baseHAM = 10000,
	baseHAMmax = 12000,
	armor = 1,
	resists = {65,35,90,90,90,-1,-1,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {},
	lootGroups = {},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(mauler_master, "mauler_master")