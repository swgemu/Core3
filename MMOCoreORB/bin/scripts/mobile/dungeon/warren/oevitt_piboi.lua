oevitt_piboi = Creature:new {
	objectName = "",
	customName = "O'Evitt Piboi (en escapee)",
	socialGroup = "warren_imperial_worker",
	faction = "",
	level = 12,
	chanceHit = 0.29,
	damageMin = 130,
	damageMax = 140,
	baseXp = 430,
	baseHAM = 1200,
	baseHAMmax = 1400,
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

	templates = {"object/mobile/warren_escapee.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "OevittPiboiConversationTemplate",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(oevitt_piboi, "oevitt_piboi")
