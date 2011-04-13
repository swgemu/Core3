battle_droid = Creature:new {
	objectName = "@mob/creature_names:battle_droid",
	socialGroup = "Death Watch",
	pvpFaction = "Death Watch",
	faction = "",
	level = 134,
	chanceHit = 5.500000,
	damageMin = 795,
	damageMax = 1300,
	baseXp = 12612,
	baseHAM = 44000,
	baseHAMmax = 54000,
	armor = 0,
	resists = {75,75,100,60,100,25,40,85,-1},
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

CreatureTemplates:addCreatureTemplate(battle_droid, "battle_droid")