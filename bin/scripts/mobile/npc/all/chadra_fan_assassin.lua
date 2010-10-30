chadra_fan_assassin = Creature:new {
	objectName = "@mob/creature_names:chadra_fan_assassin",
	socialGroup = "Chadra Fan",
	pvpFaction = "",
	faction = "",
	level = 20,
	chanceHit = 0.330000,
	damageMin = 240,
	damageMax = 250,
	baseXp = 1609,
	baseHAM = 3500,
	baseHAMmax = 4300,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
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
	creatureBitmask = KILLER + STALKER,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"pirate_weapons_heavy"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(chadra_fan_assassin, "chadra_fan_assassin")