fath_hray = Creature:new {
	objectName = "@mob/creature_names:fath_hray",
	socialGroup = "nightsister",
	faction = "nightsister",
	level = 21,
	chanceHit = 0.33,
	damageMin = 250,
	damageMax = 260,
	baseXp = 1609,
	baseHAM = 2400,
	baseHAMmax = 3000,
	armor = 0,
	resists = {0,0,0,45,45,45,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = NONE,
	creatureBitmask = NONE,
	optionsBitmask = AIENABLED + CONVERSABLE,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_fath_hray.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "theme_park_nightsister_mission_giver_convotemplate",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(fath_hray, "fath_hray")