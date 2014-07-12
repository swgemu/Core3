kafleer_tredahl = Creature:new {
	objectName = "",
	socialGroup = "townsperson",
	pvpFaction = "",
	faction = "",
	level = 16,
	chanceHit = 0.310000,
	damageMin = 160,
	damageMax = 170,
	baseXp = 1102,
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
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = NONE,
	optionsBitmask = 136,
	creatureBitmask = NONE,
	diet = HERBIVORE,

	templates = { "object/mobile/dressed_criminal_smuggler_human_male_01.iff" },
	lootGroups = {},
	weapons = {},
	conversationTemplate = "chertyl_ruluwoor_mission_target_convotemplate",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(kafleer_tredahl, "kafleer_tredahl")