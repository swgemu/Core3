pharple = Creature:new {
	objectName = "@mob/creature_names:pharple",
	socialGroup = "pharple",
	faction = "",
	level = 5,
	chanceHit = 0.25,
	damageMin = 45,
	damageMax = 50,
	baseXp = 113,
	baseHAM = 135,
	baseHAMmax = 165,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_avian",
	meatAmount = 18,
	hideType = "hide_bristley",
	hideAmount = 10,
	boneType = "bone_avian",
	boneAmount = 7,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/pharple_hue.iff"},
	hues = { 8, 9, 10, 11, 12, 13, 14, 15 },
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(pharple, "pharple")