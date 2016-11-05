crackdown_rebel_sharpshooter_hard = Creature:new {
	objectName = "@mob/creature_names:crackdown_rebel_sharpshooter_hard",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "rebel",
	faction = "rebel",
	level = 57,
	chanceHit = 0.58,
	damageMin = 460,
	damageMax = 570,
	baseXp = 5700,
	baseHAM = 10100,
	baseHAMmax = 13900,
	armor = 1,
	resists = {105,105,5,5,5,5,5,-1,-1},
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
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_rebel_trooper_bith_m_01.iff",
		"object/mobile/dressed_rebel_trooper_human_female_01.iff",
		"object/mobile/dressed_rebel_trooper_human_male_01.iff",
		"object/mobile/dressed_rebel_trooper_sullustan_male_01.iff",
		"object/mobile/dressed_rebel_trooper_twk_female_01.iff",
		"object/mobile/dressed_rebel_trooper_twk_male_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 200000},
				{group = "junk", chance = 6000000},
				{group = "weapons_all", chance = 1250000},
				{group = "armor_all", chance = 1250000},
				{group = "clothing_attachments", chance = 150000},
				{group = "armor_attachments", chance = 150000},
				{group = "wearables_all", chance = 1000000}
			}
		}
	},
	weapons = {"rebel_weapons_medium"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/military",
	personalityStf = "@hireling/hireling_military",
	attacks = merge(carbineermaster,riflemanmaster,marksmanmaster,pistoleernovice)
}

CreatureTemplates:addCreatureTemplate(crackdown_rebel_sharpshooter_hard, "crackdown_rebel_sharpshooter_hard")
