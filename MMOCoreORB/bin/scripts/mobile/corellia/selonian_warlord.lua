selonian_warlord = Creature:new {
	objectName = "@mob/creature_names:selonian_warlord",
	socialGroup = "selonian",
	pvpFaction = "",
	faction = "",
	level = 20,
	chanceHit = 0.33,
	damageMin = 180,
	damageMax = 190,
	baseXp = 1803,
	baseHAM = 4500,
	baseHAMmax = 5500,
	armor = 0,
	resists = {20,10,0,0,45,-1,-1,-1,-1},
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
	weapons = {"rebel_weapons_heavy"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(selonian_warlord, "selonian_warlord")
