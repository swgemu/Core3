corvette_neutral_bruce = Creature:new {
	objectName = "",
	customName = "Bruce Mcbrain",
	socialGroup = "jabba",
	faction = "jabba",
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
	optionsBitmask = AIENABLED + CONVERSABLE + INTERESTING + INVULNERABLE,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_corvette_neutral_bruce.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "corvetteBruceConvoTemplate",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(corvette_neutral_bruce, "corvette_neutral_bruce")