aujante_klee = Creature:new {
	objectName = "@mob/creature_names:aujante_klee",
	socialGroup = "mtn_clan",
	faction = "mtn_clan",
	level = 23,
	chanceHit = 0.33,
	damageMin = 190,
	damageMax = 200,
	baseXp = 2006,
	baseHAM = 3500,
	baseHAMmax = 4300,
	armor = 0,
	resists = {25,25,0,40,40,40,40,-1,-1},
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

	templates = {"object/mobile/dressed_aujante_klee.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "theme_park_smc_vurlene_aujante_mission_giver_convotemplate",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(aujante_klee, "aujante_klee")
