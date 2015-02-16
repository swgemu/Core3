imperial_observer = Creature:new {
	objectName = "@mob/creature_names:geonosian_imperial_observer",
	socialGroup = "imperial",
	faction = "imperial",
	level = 53,
	chanceHit = 0.54,
	damageMin = 415,
	damageMax = 540,
	baseXp = 5190,
	baseHAM = 11000,
	baseHAMmax = 13000,
	armor = 1,
	resists = {5,5,5,5,5,5,5,5,-1},
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
		"object/mobile/dressed_imperial_officer_m.iff",
		"object/mobile/dressed_imperial_officer_m_2.iff",
		"object/mobile/dressed_imperial_officer_m_3.iff",
		"object/mobile/dressed_imperial_officer_m_4.iff",
		"object/mobile/dressed_imperial_officer_m_5.iff",
		"object/mobile/dressed_imperial_officer_m_6.iff"},
	lootGroups = {
		{
			groups = {
				{group = "clothing_attachments", chance = 350000},
				{group = "armor_attachments", chance = 350000},
				{group = "geonosian_hard", chance = 900000},
				{group = "geonosian_common", chance = 4200000},
				{group = "geonosian_relic", chance = 4200000}
			},
			lootChance = 3000000
		}
	},
	weapons = {"imperial_weapons_heavy"},
	conversationTemplate = "",
	attacks = merge(brawlermaster,marksmanmaster,riflemanmaster,carbineermaster)
}

CreatureTemplates:addCreatureTemplate(imperial_observer, "imperial_observer")
