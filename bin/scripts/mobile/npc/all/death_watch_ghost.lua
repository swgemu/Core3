death_watch_ghost = Creature:new {
	objectName = "Death Watch Ghost",
	socialGroup = "Death Watch",
	pvpFaction = "Death Watch",
	faction = "",
	level = 152,
	chanceHit = 8.500000,
	damageMin = 895,
	damageMax = 1500,
	baseXp = 14314,
	baseHAM = 81000,
	baseHAMmax = 99000,
	armor = 0,
	resists = {65,65,70,60,35,35,100,50,-1},
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
	creatureBitmask = KILLER,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"pirate_weapons_heavy"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(death_watch_ghost, "death_watch_ghost")