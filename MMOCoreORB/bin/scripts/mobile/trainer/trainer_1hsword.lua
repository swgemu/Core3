trainer_1hsword = Creature:new {
	objectName = "@mob/creature_names:trainer_1hsword",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "",
	faction = "",
	level = 100,
	chanceHit = 0.39,
	damageMin = 290,
	damageMax = 300,
	baseXp = 2914,
	baseHAM = 8400,
	baseHAMmax = 10200,
	armor = 0,
	resists = {-1,-1,-1,-1,-1,-1,-1,-1,-1},
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
	optionsBitmask = INVULNERABLE + CONVERSABLE,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_1handsword_trainer_01.iff",
		"object/mobile/dressed_1handsword_trainer_02.iff",
		"object/mobile/dressed_1handsword_trainer_03.iff"
	},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "1hswordTrainerConvoTemplate",
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(trainer_1hsword, "trainer_1hsword")