enraged_donkuwah = Creature:new {
	objectName = "@mob/creature_names:enraged_donkuwah",
	socialGroup = "Donkuwah Tr.",
	pvpFaction = "Donkuwah Tr.",
	faction = "",
	level = 34,
	chanceHit = 0.400000,
	damageMin = 335,
	damageMax = 380,
	baseXp = 3460,
	baseHAM = 8200,
	baseHAMmax = 10000,
	armor = 0,
	resists = {35,35,0,60,60,-1,0,-1,-1},
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

CreatureTemplates:addCreatureTemplate(enraged_donkuwah, "enraged_donkuwah")