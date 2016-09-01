informant_quest_crev = Creature:new {
	objectName = "@mob/creature_names:spynet_operative",
	socialGroup = "spynet",
	faction = "",
	level = 17,
	chanceHit = 0.32,
	damageMin = 160,
	damageMax = 170,
	baseXp = 1257,
	baseHAM = 3500,
	baseHAMmax = 4300,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
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
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED + CONVERSABLE,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_eisley_officer_bothan_female_01.iff",
		"object/mobile/dressed_eisley_officer_bothan_male_01.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "crev_bombaasa_mission_target_convotemplate",
	reactionStf = "@npc_reaction/slang",
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(informant_quest_crev, "informant_quest_crev")
