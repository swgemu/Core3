death_watch_wraith = Creature:new {
	objectName = "Death Watch Wraith",
	socialGroup = "Death Watch",
	pvpFaction = "Death Watch",
	faction = "",
	level = 178,
	chanceHit = 12.250000,
	damageMin = 1020,
	damageMax = 1750,
	baseXp = 16794,
	baseHAM = 118000,
	baseHAMmax = 144000,
	armor = 0,
	resists = {75,75,90,80,45,45,100,70,-1},
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

CreatureTemplates:addCreatureTemplate(death_watch_wraith, "death_watch_wraith")