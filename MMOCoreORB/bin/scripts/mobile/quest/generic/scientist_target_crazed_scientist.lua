scientist_target_crazed_scientist = Creature:new {
	objectName = "@mob/creature_names:scientist",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "thug",
	faction = "thug",
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
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 6000000},
				{group = "wearables_common", chance = 2000000},
				{group = "pistols", chance = 1000000},
				{group = "melee_weapons", chance = 1000000},
			}
		}
	},
	weapons = {"pirate_weapons_light"},
	conversationTemplate = "",
	attacks = merge(marksmannovice,brawlernovice)
}

CreatureTemplates:addCreatureTemplate(scientist_target_crazed_scientist, "scientist_target_crazed_scientist")
