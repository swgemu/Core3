pharple = Creature:new {
	objectName = "@mob/creature_names:pharple",
	socialGroup = "pharple",
	pvpFaction = "",
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
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/pharple.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(pharple, "pharple")