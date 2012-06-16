scientist = Creature:new {
	objectName = "@mob/creature_names:scientist",
	socialGroup = "townsperson",
	pvpFaction = "townsperson",
	faction = "townsperson",
	level = 34,
	chanceHit = 0.410000,
	damageMin = 320,
	damageMax = 350,
	baseXp = 3279,
	baseHAM = 8800,
	baseHAMmax = 10800,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
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
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(scientist, "scientist")