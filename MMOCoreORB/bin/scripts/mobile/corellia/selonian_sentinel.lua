selonian_sentinel = Creature:new {
	objectName = "@mob/creature_names:selonian_sentinel",
	socialGroup = "selonian",
	pvpFaction = "",
	faction = "",
	level = 9,
	chanceHit = 0.27,
	damageMin = 70,
	damageMax = 75,
	baseXp = 0,
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
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_selonian_f_01.iff",
		"object/mobile/dressed_selonian_f_02.iff",
		"object/mobile/dressed_selonian_f_03.iff",
		"object/mobile/dressed_selonian_f_04.iff",
		"object/mobile/dressed_selonian_f_05.iff",
		"object/mobile/dressed_selonian_f_06.iff",
		"object/mobile/dressed_selonian_f_07.iff",
		"object/mobile/dressed_selonian_f_08.iff",
		"object/mobile/dressed_selonian_f_09.iff",
		"object/mobile/dressed_selonian_f_10.iff",
		"object/mobile/dressed_selonian_f_11.iff",
		"object/mobile/dressed_selonian_f_12.iff",
		"object/mobile/dressed_selonian_m_01.iff",
		"object/mobile/dressed_selonian_m_02.iff",
		"object/mobile/dressed_selonian_m_03.iff",
		"object/mobile/dressed_selonian_m_04.iff",
		"object/mobile/dressed_selonian_m_05.iff",
		"object/mobile/dressed_selonian_m_06.iff",
		"object/mobile/dressed_selonian_m_07.iff",
		"object/mobile/dressed_selonian_m_08.iff",
		"object/mobile/dressed_selonian_m_09.iff",
		"object/mobile/dressed_selonian_m_10.iff",
		"object/mobile/dressed_selonian_m_11.iff",
		"object/mobile/dressed_selonian_m_12.iff"},
	lootGroups = {
      	{
			groups = {
				{group = "junk", chance = 6000000},
				{group = "loot_kits", chance = 3500000},
				{group = "tailor_components", chance = 500000}
			},
			lootChance = 6500000
		}	
	},
	weapons = {"pirate_weapons_medium"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(selonian_sentinel, "selonian_sentinel")
