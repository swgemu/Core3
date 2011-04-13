death_watch_overlord = Creature:new {
	objectName = "Death Watch Overlord",
	socialGroup = "Death Watch",
	pvpFaction = "Death Watch",
	faction = "",
	level = 221,
	chanceHit = 19.000000,
	damageMin = 1245,
	damageMax = 2200,
	baseXp = 20948,
	baseHAM = 198000,
	baseHAMmax = 242000,
	armor = 0,
	resists = {80,80,90,80,45,45,100,70,-1},
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

CreatureTemplates:addCreatureTemplate(death_watch_overlord, "death_watch_overlord")