crackdown_comm_operator_hard = Creature:new {
	objectName = "@mob/creature_names:crackdown_comm_operator_hard",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "imperial",
	faction = "imperial",
	level = 48,
	chanceHit = 0.49,
	damageMin = 385,
	damageMax = 480,
	baseXp = 4800,
	baseHAM = 10100,
	baseHAMmax = 12300,
	armor = 1,
	resists = {0,0,0,0,0,0,0,0,-1},
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
		"object/mobile/dressed_imperial_officer_m.iff",
		"object/mobile/dressed_imperial_officer_f.iff",
		"object/mobile/dressed_imperial_officer_m_2.iff",
		"object/mobile/dressed_imperial_officer_m_3.iff",
		"object/mobile/dressed_imperial_officer_m_4.iff",
		"object/mobile/dressed_imperial_officer_m_5.iff",
		"object/mobile/dressed_imperial_officer_m_6.iff"
		},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 100000},
				{group = "junk", chance = 7650000},
				{group = "rifles", chance = 550000},
				{group = "pistols", chance = 550000},
				{group = "melee_weapons", chance = 550000},
				{group = "carbines", chance = 550000},
				{group = "clothing_attachments", chance = 25000},
				{group = "armor_attachments", chance = 25000}
			},
			lootChance = 2800000
		}
	},
	weapons = {"imperial_weapons_light"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/military",
	personalityStf = "@hireling/hireling_military",
	attacks = merge(pistoleermid,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(crackdown_comm_operator_hard, "crackdown_comm_operator_hard")
