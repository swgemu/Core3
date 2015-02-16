maestro = Creature:new {
	objectName = "",
	customName = "Maestro",
	socialGroup = "",
	faction = "",
	level = 7,
	chanceHit = 0.26,
	damageMin = 55,
	damageMax = 65,
	baseXp = 187,
	baseHAM = 700,
	baseHAMmax = 800,
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

	templates = {
			"object/mobile/dressed_noble_old_human_male_01.iff",
			"object/mobile/dressed_noble_fat_human_male_01.iff",
			"object/mobile/dressed_noble_fat_zabrak_male_01.iff",
			"object/mobile/dressed_noble_human_male_04.iff"
				},
	lootGroups = {				
	},
	weapons = {"rebel_weapons_medium"},
	conversationTemplate = "hefsen_zindalai_mission_target_convotemplate",
	attacks = merge(brawlernovice,marksmannovice)
}

CreatureTemplates:addCreatureTemplate(maestro, "maestro")