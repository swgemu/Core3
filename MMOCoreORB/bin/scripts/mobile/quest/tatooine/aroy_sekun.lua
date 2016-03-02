aroy_sekun = Creature:new {
	objectName = "",
	customName = "Aroy Sekun",
	socialGroup = "townsperson",
	faction = "townsperson",
	level = 7,
	chanceHit = 0.26,
	damageMin = 55,
	damageMax = 65,
	baseXp = 187,
	baseHAM = 270,
	baseHAMmax = 330,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED + CONVERSABLE,
	diet = HERBIVORE,

	templates = {
					"object/mobile/dressed_quest_farmer.iff",
					"object/mobile/dressed_commoner_naboo_human_male_02.iff",
					"object/mobile/dressed_commoner_fat_human_male_01.iff"
		},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "melios_purl_mission_target_convotemplate",
	attacks = brawlermaster
}

CreatureTemplates:addCreatureTemplate(aroy_sekun, "aroy_sekun")
