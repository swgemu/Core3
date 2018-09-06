biogenic_scientist_human = Creature:new {
	objectName = "@mob/creature_names:geonosian_scientist",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "self",
	faction = "",
	level = 25,
	chanceHit = 0.35,
	damageMin = 120,
	damageMax = 230,
	baseXp = 4300,
	baseHAM = 6500,
	baseHAMmax = 7400,
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
	optionsBitmask = AIENABLED + INVULNERABLE + INTERESTING + CONVERSABLE,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_doctor_trainer_human_female_01.iff",
		"object/mobile/dressed_combatmedic_trainer_human_female_01.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "biogenicScientistHumanConvoTemplate",
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(biogenic_scientist_human, "biogenic_scientist_human")
