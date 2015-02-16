dr_kaum = Creature:new {
	objectName = "",
	faction = "",
	level = 4,
	chanceHit = 0.24,
	damageMin = 40,
	damageMax = 45,
	baseXp = 62,
	baseHAM = 113,
	baseHAMmax = 138,
	armor = 0,
	resists = {-1,-1,-1,-1,-1,-1,-1,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = NONE,
	optionsBitmask = 136,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_weaponsmith_trainer_01.iff",
		"object/mobile/dressed_weaponsmith_trainer_02.iff",
		"object/mobile/dressed_weaponsmith_trainer_03.iff"
	},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "theme_park_valarian_mission_target_convotemplate",
	attacks = brawlermaster
}
CreatureTemplates:addCreatureTemplate(dr_kaum,"dr_kaum")
