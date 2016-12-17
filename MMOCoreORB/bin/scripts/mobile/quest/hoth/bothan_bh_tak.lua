bothan_bh_tak = Creature:new {
	objectName = "@mob/creature_names:bothan_diplomat",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "townsperson",
	faction = "townsperson",
	level = 115,
	chanceHit = 1,
	damageMin = 820,
	damageMax = 1350,
	baseXp = 10087,
	baseHAM = 24000,
	baseHAMmax = 30000,
	armor = 0,
	resists = {55,55,55,45,155,55,55,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = NONE,
	creatureBitmask = HERD,
	optionsBitmask = AIENABLED + CONVERSABLE,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_bth_spynet_pilot_m_01.iff",
		"object/mobile/dressed_eisley_officer_bothan_male_01.iff"
	},

	lootGroups = {},
	weapons = {},
	conversationTemplate = "takhomasak_mission_target_convotemplate",
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(bothan_bh_tak, "bothan_bh_tak")
