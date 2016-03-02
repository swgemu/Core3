naboo_kidnapped_noble_03 = Creature:new {
	objectName = "",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	customName = "a Kidnapped Noble",
	socialGroup = "townsperson",
	faction = "townsperson",
	level = 20,
	chanceHit = 0.33,
	damageMin = 190,
	damageMax = 200,
	baseXp = 1609,
	baseHAM = 5000,
	baseHAMmax = 6100,
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

	templates = {
		"object/mobile/dressed_noble_naboo_twilek_male_01.iff"
	},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "kidnappedNobleConvoTemplate",
	attacks = brawlermaster
}

CreatureTemplates:addCreatureTemplate(naboo_kidnapped_noble_03, "naboo_kidnapped_noble_03")
