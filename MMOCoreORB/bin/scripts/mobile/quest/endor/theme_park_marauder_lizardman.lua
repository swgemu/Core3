theme_park_marauder_lizardman = Creature:new {
	objectName = "@npc_name:trandoshan_base_male",
	customName = "Lizardman",
	socialGroup = "",
	faction = "",
	level = 10,
	chanceHit = 0.26,
	damageMin = 55,
	damageMax = 65,
	baseXp = 187,
	baseHAM = 900,
	baseHAMmax = 1000,
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
	creatureBitmask = PACK + HERD,
	optionsBitmask = 264,
	diet = HERBIVORE,

	templates =
			{
			"object/mobile/trandoshan_male.iff",
			"object/mobile/dressed_cobral_runner_trandoshan_male_01.iff",
			"object/mobile/dressed_commoner_tatooine_trandoshan_male_01.iff"
			},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "theme_park_marauder_mission_target_convotemplate",
	attacks = brawlernovice
}

CreatureTemplates:addCreatureTemplate(theme_park_marauder_lizardman, "theme_park_marauder_lizardman")
