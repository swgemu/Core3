panic_npc_1 = Creature:new {
	objectName = "@mob/creature_names:commoner",
	socialGroup = "Imperial",
	pvpFaction = "",
	faction = "",
	level = 30,
	chanceHit = 0.390000,
	damageMin = 290,
	damageMax = 300,
	baseXp = 2914,
	baseHAM = 8400,
	baseHAMmax = 10200,
	armor = 0,
	resists = {0,45,0,-1,40,-1,40,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = NONE,
	creatureBitmask = NONE,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_commoner_tatooine_bith_male_05.iff"},
	lootgroups = {},
	weapons = {"imperial_weapons_medium"},
	attacks = {},
	conversationTemplate = "panic_npc_1_convotemplate",--dont change this
	optionsBitmask = 264
}

CreatureTemplates:addCreatureTemplate(panic_npc_1, "panic_npc_1")
