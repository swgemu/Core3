clientrep_quest_green = Creature:new {
	objectName = "@mob/creature_names:assassin_mission_recruiter_neutral",
	socialGroup = "hutt",
	faction = "",
	level = 16,
	chanceHit = 0.31,
	damageMin = 160,
	damageMax = 170,
	baseXp = 831,
	baseHAM = 2900,
	baseHAMmax = 3500,
	armor = 0,
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
	pvpBitmask = NONE,
	creatureBitmask = NONE,
	optionsBitmask = AIENABLED + CONVERSABLE,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_assassin_mission_giver_01.iff",
		"object/mobile/dressed_assassin_mission_giver_02.iff",
		"object/mobile/dressed_assassin_mission_giver_03.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "green_laser_mission_target_convotemplate",
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(clientrep_quest_green, "clientrep_quest_green")
