kobola_assassin = Creature:new {
	objectName = "@mob/creature_names:kobola_assassin",
	socialGroup = "Kobola",
	pvpFaction = "Kobola",
	faction = "",
	level = 18,
	chanceHit = 0.320000,
	damageMin = 200,
	damageMax = 210,
	baseXp = 1426,
	baseHAM = 1500,
	baseHAMmax = 1900,
	armor = 0,
	resists = {20,10,0,0,0,0,0,-1,-1},
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
	creatureBitmask = PACK + KILLER + STALKER,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"pirate_weapons_heavy"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(kobola_assassin, "kobola_assassin")