vile_donkuwah_battlelord = Creature:new {
	objectName = "@mob/creature_names:vile_donkuwah_battlelord",
	socialGroup = "Donkuwah Tr.",
	pvpFaction = "Donkuwah Tr.",
	faction = "",
	level = 34,
	chanceHit = 0.420000,
	damageMin = 360,
	damageMax = 430,
	baseXp = 3460,
	baseHAM = 8600,
	baseHAMmax = 10500,
	armor = 0,
	resists = {50,-1,0,50,50,-1,0,-1,-1},
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

CreatureTemplates:addCreatureTemplate(vile_donkuwah_battlelord, "vile_donkuwah_battlelord")