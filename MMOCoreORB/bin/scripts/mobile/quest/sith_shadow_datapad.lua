sith_shadow_datapad = Creature:new {
	objectName = "@mob/creature_names:shadow_punk",
	socialGroup = "sith_shadow",
	pvpFaction = "sith_shadow",
	faction = "sith_shadow",
	level = 10,
	chanceHit = 0.28,
	damageMin = 90,
	damageMax = 110,
	baseXp = 356,
	baseHAM = 810,
	baseHAMmax = 990,
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
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_sith_shadow_hum_f_01.iff",
		"object/mobile/dressed_sith_shadow_hum_f_02.iff",
		"object/mobile/dressed_sith_shadow_hum_f_03.iff",
		"object/mobile/dressed_sith_shadow_hum_m_01.iff",
		"object/mobile/dressed_sith_shadow_hum_m_02.iff",
		"object/mobile/dressed_sith_shadow_hum_m_03.iff",
		"object/mobile/dressed_sith_shadow_aqualish_f_01.iff",
		"object/mobile/dressed_sith_shadow_aqualish_f_02.iff",
		"object/mobile/dressed_sith_shadow_aqualish_m_01.iff",
		"object/mobile/dressed_sith_shadow_aqualish_m_02.iff",
		"object/mobile/dressed_sith_shadow_nikto_m_01.iff",
		"object/mobile/dressed_sith_shadow_nikto_m_02.iff",
		"object/mobile/dressed_sith_shadow_nikto_m_03.iff",
		"object/mobile/dressed_sith_shadow_rodian_f_01.iff",
		"object/mobile/dressed_sith_shadow_rodian_f_02.iff",
		"object/mobile/dressed_sith_shadow_rodian_m_01.iff",
		"object/mobile/dressed_sith_shadow_rodian_m_02.iff",
		"object/mobile/dressed_sith_shadow_trn_f_01.iff",
		"object/mobile/dressed_sith_shadow_trn_m_01.iff",
		"object/mobile/dressed_sith_shadow_trn_m_02.iff",
		"object/mobile/dressed_sith_shadow_trn_m_03.iff",
		"object/mobile/dressed_sith_shadow_zab_f_01.iff",
		"object/mobile/dressed_sith_shadow_zab_f_02.iff",
		"object/mobile/dressed_sith_shadow_zab_m_01.iff",
		"object/mobile/dressed_sith_shadow_zab_m_02.iff",
		"object/mobile/dressed_sith_shadow_zab_m_03.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "sith_shadow_encounter_datapad", chance = 10000000}
			},
			lootChance = 10000000
		}
	},
	weapons = {"pirate_weapons_light"},
	conversationTemplate = "",
	attacks = merge(brawlernovice,marksmannovice)
}

CreatureTemplates:addCreatureTemplate(sith_shadow_datapad, "sith_shadow_datapad")
