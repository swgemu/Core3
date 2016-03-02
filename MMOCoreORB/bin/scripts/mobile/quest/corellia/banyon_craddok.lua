banyon_craddok = Creature:new {
	objectName = "",
	socialGroup = "",
	faction = "",
	level = 15,
	chanceHit = 0.31,
	damageMin = 160,
	damageMax = 170,
	baseXp = 831,
	baseHAM = 2400,
	baseHAMmax = 3000,
	armor = 0,
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
	pvpBitmask = NONE,
	creatureBitmask = NONE,
	optionsBitmask = AIENABLED + CONVERSABLE,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_corsec_detective_human_male_01.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "noren_krast_mission_target_convotemplate",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(banyon_craddok, "banyon_craddok")
