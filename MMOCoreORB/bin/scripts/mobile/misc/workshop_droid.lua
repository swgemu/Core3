workshop_droid = Creature:new {
	objectName = "@droid_name:wed_treadwell_base",
	customName = "WED15-I643 (a workshop droid)",
	socialGroup = "",
	pvpFaction = "",
	faction = "",
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

	aiTemplate = "default",

	templates = {"object/mobile/wed_treadwell.iff"},
	lootGroups = {},
	weapons = {},
	attacks = {},
	conversationTemplate = "workshop_droid_convotemplate",
	optionsBitmask = 264
}

CreatureTemplates:addCreatureTemplate(workshop_droid, "workshop_droid")
