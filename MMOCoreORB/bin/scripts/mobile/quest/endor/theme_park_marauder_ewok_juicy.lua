theme_park_marauder_ewok_juicy = Creature:new {
	objectName = "@npc_name:ewok_base_male",
	customName = "Juicy Ewok",
	socialGroup = "gondula_tribe",
	faction = "gondula_tribe",
	level = 35,
	chanceHit = 0.41,
	damageMin = 325,
	damageMax = 360,
	baseXp = 3460,
	baseHAM = 8700,
	baseHAMmax = 10700,
	armor = 0,
	resists = {60,60,60,60,60,60,60,60,-1},
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
	optionsBitmask = 264,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_ewok_m_04.iff",
		"object/mobile/dressed_ewok_m_05.iff",
		"object/mobile/ewok_male.iff"},
	lootGroups = {},
	weapons = {"ewok_weapons"},
	conversationTemplate = "theme_park_marauder_mission_target_convotemplate",
	attacks = merge(riflemanmaster,brawlermaster)
}
CreatureTemplates:addCreatureTemplate(theme_park_marauder_ewok_juicy, "theme_park_marauder_ewok_juicy")
