gondula_loremaster = Creature:new {
	objectName = "@mob/creature_names:gondula_loremaster",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "gondula_tribe",
	faction = "gondula_tribe",
	level = 20,
	chanceHit = 0.33,
	damageMin = 180,
	damageMax = 190,
	baseXp = 1609,
	baseHAM = 4500,
	baseHAMmax = 5500,
	armor = 0,
	resists = {0,0,0,35,35,-1,-1,-1,-1},
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
		"object/mobile/dressed_ewok_f_05.iff",
		"object/mobile/dressed_ewok_f_10.iff",
		"object/mobile/dressed_ewok_f_11.iff",
		"object/mobile/dressed_ewok_m_05.iff",
		"object/mobile/dressed_ewok_m_10.iff",
		"object/mobile/dressed_ewok_m_12.iff"},
	lootGroups = {
		{
			groups = {
				{group = "ewok", chance = 10000000}
			},
			lootChance = 1400000
		}
	},
	weapons = {"ewok_weapons"},
	conversationTemplate = "",
	attacks = merge(marksmanmaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(gondula_loremaster, "gondula_loremaster")
