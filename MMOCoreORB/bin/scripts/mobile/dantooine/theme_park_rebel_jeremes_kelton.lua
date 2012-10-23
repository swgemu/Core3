theme_park_rebel_jeremes_kelton = Creature:new {
	objectName = "",
	socialGroup = "rebel",
	pvpFaction = "rebel",
	faction = "rebel",
	level = 100,
	chanceHit = 1,
	damageMin = 645,
	damageMax = 1000,
	baseXp = 9429,
	baseHAM = 24000,
	baseHAMmax = 30000,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
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
	creatureBitmask = PACK,
	optionsBitmask = 264,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_rebel_specforce_captain_human_male_01.iff",
				 "object/mobile/dressed_rebel_specforce_general_sullustan_male_01.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "theme_park_rebel_mission_target_convotemplate",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(theme_park_rebel_jeremes_kelton, "theme_park_rebel_jeremes_kelton")