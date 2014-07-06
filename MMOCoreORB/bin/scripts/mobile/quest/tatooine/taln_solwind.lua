taln_solwind = Creature:new {
	objectName = "",
	socialGroup = "townsperson",
	pvpFaction = "townsperson",
	faction = "townsperson",
	level = 4,
	chanceHit = 0.24,
	damageMin = 40,
	damageMax = 45,
	baseXp = 62,
	baseHAM = 113,
	baseHAMmax = 138,
	armor = 0,
	resists = {15,15,15,15,15,15,15,-1,-1},
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
	creatureBitmask = HERD,
	optionsBitmask = 136,
	diet = HERBIVORE,

	templates = {
				"object/mobile/dressed_commoner_artisan_trandoshan_male_01.iff",
				"object/mobile/dressed_commoner_artisan_bith_male_01.iff",
				"object/mobile/dressed_commoner_artisan_sullustan_male_01.iff",
				"object/mobile/dressed_artisan_trainer_01.iff",
					},
				
	lootGroups = {},
	weapons = {},
	conversationTemplate = "ikka_gesul_mission_target_convotemplate",
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(taln_solwind, "taln_solwind")