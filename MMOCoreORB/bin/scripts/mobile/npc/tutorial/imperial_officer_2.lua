imperial_officer_tutorial_2 = Creature:new {
	objectName = "@mob/creature_names:warren_imperial_officer",
	socialGroup = "Imperial",
	pvpFaction = "Imperial",
	faction = "imperial",
	level = 30,
	chanceHit = 0.390000,
	damageMin = 290,
	damageMax = 300,
	baseXp = 2914,
	baseHAM = 8400,
	baseHAMmax = 10200,
	armor = 0,
	resists = {0,45,0,-1,40,-1,40,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = NONE,
	creatureBitmask = NONE,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_imperial_officer_m.iff"},
	lootGroups = {},
	weapons = {"imperial_weapons_medium"},
	attacks = {},
	conversationTemplate = "imperial_officer_2_convotemplate",--dont change this
	optionsBitmask = 264
}

CreatureTemplates:addCreatureTemplate(imperial_officer_tutorial_2, "imperial_officer_tutorial_2")