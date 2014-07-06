kaeline_ungasan = Creature:new {
	objectName = "@npc_name:human_base_male",
	customName = "Kaeline Ungasan",
	socialGroup = "townsperson",
	pvpFaction = "townsperson",
	faction = "townsperson",
	level = 11,
	chanceHit = 0.28,
	damageMin = 90,
	damageMax = 110,
	baseXp = 356,
	baseHAM = 810,
	baseHAMmax = 990,
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
	optionsBitmask = 136,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_tatooine_kaeline_ungasan.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "kaeline_ungasan_mission_giver_convotemplate",
	outfit = "kaeline_ungasan_outfit",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(kaeline_ungasan, "kaeline_ungasan")
