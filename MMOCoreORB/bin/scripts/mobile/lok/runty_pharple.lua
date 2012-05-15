runty_pharple = Creature:new {
	objectName = "@mob/creature_names:runty_pharple",
	socialGroup = "pharple",
	pvpFaction = "",
	faction = "",
	level = 3,
	chanceHit = 0.23,
	damageMin = 35,
	damageMax = 45,
	baseXp = 62,
	baseHAM = 90,
	baseHAMmax = 110,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_avian",
	meatAmount = 15,
	hideType = "hide_bristley",
	hideAmount = 7,
	boneType = "bone_avian",
	boneAmount = 5,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/runty_pharple.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(runty_pharple, "runty_pharple")