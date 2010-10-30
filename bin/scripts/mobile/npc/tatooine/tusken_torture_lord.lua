tusken_torture_lord = Creature:new {
	objectName = "@mob/creature_names:tusken_torture_lord",
	socialGroup = "Tusken Raider",
	pvpFaction = "Tusken Raider",
	faction = "",
	level = 57,
	chanceHit = 0.570000,
	damageMin = 430,
	damageMax = 570,
	baseXp = 5555,
	baseHAM = 11000,
	baseHAMmax = 13000,
	armor = 0,
	resists = {50,30,0,60,-1,30,-1,-1,-1},
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
	creatureBitmask = PACK + KILLER + STALKER,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"tusken_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(tusken_torture_lord, "tusken_torture_lord")