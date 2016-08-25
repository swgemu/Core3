imperial_courier_quest_bardo2 = Creature:new {
	objectName = "@mob/creature_names:assassin_mission_recruiter_imperial",
	level = 13,
	chanceHit = 0.3,
	damageMin = 140,
	damageMax = 150,
	baseXp = 609,
	baseHAM = 1500,
	baseHAMmax = 1900,
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
	optionsBitmask = AIENABLED + CONVERSABLE,
	creatureBitmask = NONE,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_imperial_red_f.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "bardo_klinj_mission_target_convotemplate",
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(imperial_courier_quest_bardo2, "imperial_courier_quest_bardo2")
