vicious_donkuwah_battlelord = Creature:new {
	objectName = "@mob/creature_names:vicious_donkuwah_battlelord",
	socialGroup = "Donkuwah Tr.",
	pvpFaction = "Donkuwah Tr.",
	faction = "",
	level = 51,
	chanceHit = 0.510000,
	damageMin = 425,
	damageMax = 560,
	baseXp = 5007,
	baseHAM = 10000,
	baseHAMmax = 12200,
	armor = 0,
	resists = {35,0,0,50,50,-1,0,-1,-1},
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

CreatureTemplates:addCreatureTemplate(vicious_donkuwah_battlelord, "vicious_donkuwah_battlelord")