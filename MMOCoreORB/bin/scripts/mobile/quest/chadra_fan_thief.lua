chadra_fan_thief = Creature:new {
	objectName = "@mob/creature_names:chadra_fan_thief",
	socialGroup = "chadra_fan",
	faction = "",
	level = 8,
	chanceHit = 0.27,
	damageMin = 70,
	damageMax = 75,
	baseXp = 187,
	baseHAM = 405,
	baseHAMmax = 495,
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
	creatureBitmask = STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/chadra_fan_female.iff",
		"object/mobile/dressed_chadra_fan_f_01.iff",
		"object/mobile/dressed_chadra_fan_f_02.iff",
		"object/mobile/dressed_chadra_fan_f_03.iff",
		"object/mobile/chadra_fan_male.iff",
		"object/mobile/dressed_chadra_fan_m_01.iff",
		"object/mobile/dressed_chadra_fan_m_02.iff",
		"object/mobile/dressed_chadra_fan_m_03.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 5000000},
				{group = "tailor_components", chance = 1500000},
				{group = "loot_kit_parts", chance = 2000000},
				{group = "wearables_common", chance = 1500000}
			}
		}
	},
	weapons = {"pirate_weapons_medium"},
	conversationTemplate = "",
	attacks = merge(marksmannovice,brawlernovice)
}

CreatureTemplates:addCreatureTemplate(chadra_fan_thief, "chadra_fan_thief")
