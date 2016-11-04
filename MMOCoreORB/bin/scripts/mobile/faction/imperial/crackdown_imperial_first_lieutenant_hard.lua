crackdown_imperial_first_lieutenant_hard = Creature:new {
	objectName = "@mob/creature_names:crackdown_imperial_first_lieutenant_hard",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "imperial",
	faction = "imperial",
	level = 61,
	chanceHit = 0.63,
	damageMin = 450,
	damageMax = 600,
	baseXp = 6045,
	baseHAM = 11500,
	baseHAMmax = 16100,
	armor = 1,
	resists = {10,10,10,10,10,10,10,-1,-1},
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
	optionsBitmask = AIENABLED + CONVERSABLE,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_imperial_lieutenant_m.iff",
		"object/mobile/dressed_imperial_officer_m_3.iff",
		"object/mobile/dressed_imperial_officer_m_5.iff"
	},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 100000},
				{group = "junk", chance = 7200000},
				{group = "rifles", chance = 550000},
				{group = "pistols", chance = 550000},
				{group = "melee_weapons", chance = 550000},
				{group = "carbines", chance = 550000},
				{group = "clothing_attachments", chance = 25000},
				{group = "armor_attachments", chance = 25000},
				{group = "imperial_officer_common", chance = 450000}
			},
			lootChance = 2800000
		}
	},
	weapons = {"imperial_weapons_medium"},
	conversationTemplate = "imperialRecruiterConvoTemplate",
	reactionStf = "@npc_reaction/military",
	personalityStf = "@hireling/hireling_military",
	attacks = merge(riflemanmaster,carbineermaster)
}

CreatureTemplates:addCreatureTemplate(crackdown_imperial_first_lieutenant_hard, "crackdown_imperial_first_lieutenant_hard")
