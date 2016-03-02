mat_rags = Creature:new {
	objectName = "@npc_name:human_base_male",
	customName = "Mat Rags",
	socialGroup = "townsperson",
	faction = "townsperson",
	level = 100,
	chanceHit = 1,
	damageMin = 645,
	damageMax = 1000,
	baseXp = 9429,
	baseHAM = 24000,
	baseHAMmax = 30000,
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
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED + CONVERSABLE,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_tatooine_mat_rags.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "mat_rags_mission_giver_convotemplate",
	outfit = "mat_rags_outfit",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(mat_rags, "mat_rags")
