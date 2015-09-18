fbase_imperial_warrant_officer_ii = Creature:new {
	objectName = "@mob/creature_names:fbase_imperial_warrant_officer_ii",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "imperial",
	faction = "imperial",
	level = 28,
	chanceHit = 0.39,
	damageMin = 270,
	damageMax = 280,
	baseXp = 2800,
	baseHAM = 8200,
	baseHAMmax = 10000,
	armor = 0,
	resists = {5,5,5,5,5,5,5,-1,-1},
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
	optionsBitmask = 136,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_imperial_officer_f.iff",
		"object/mobile/dressed_imperial_officer_m.iff",
		"object/mobile/dressed_imperial_officer_m_2.iff",
		"object/mobile/dressed_imperial_officer_m_3.iff",
		"object/mobile/dressed_imperial_officer_m_4.iff",
		"object/mobile/dressed_imperial_officer_m_5.iff",
		"object/mobile/dressed_imperial_officer_m_6.iff"},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 100000},
				{group = "junk", chance = 6000000},
				{group = "weapons_all", chance = 1100000},
				{group = "armor_all", chance = 1100000},
				{group = "clothing_attachments", chance = 150000},
				{group = "armor_attachments", chance = 150000},
				{group = "imperial_officer_common", chance = 400000},
				{group = "wearables_all", chance = 1000000}
			}
		}
	},
	weapons = {"imperial_weapons_medium"},
	conversationTemplate = "imperialRecruiterConvoTemplate",
	reactionStf = "@npc_reaction/military",
	attacks = merge(brawlermaster,marksmanmaster,carbineermid)
}

CreatureTemplates:addCreatureTemplate(fbase_imperial_warrant_officer_ii, "fbase_imperial_warrant_officer_ii")
