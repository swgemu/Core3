ris_inventor = Creature:new {
	objectName = "",
	customName = "an R.I.S. Inventor",
	generateRandomName = true,
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
	pvpBitmask = NONE,
	creatureBitmask = NONE,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
					"object/mobile/dressed_combatmedic_trainer_human_male_01.iff", 
					"object/mobile/dressed_brigade_captain_human_male_01.iff",
					"object/mobile/dressed_hutt_medic2_twilek_male_01.iff",
					"object/mobile/dressed_combatmedic_trainer_human_female_01.iff",
					"object/mobile/dressed_doctor_trainer_moncal_male_01.iff",
					"object/mobile/dressed_combatmedic_trainer_rodian_male_01.iff",
					"object/mobile/dressed_mercenary_medic_rodian_female_01.iff"
					},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(ris_inventor, "ris_inventor")
