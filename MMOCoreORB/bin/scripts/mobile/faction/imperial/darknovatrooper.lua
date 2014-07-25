darknovatrooper = Creature:new {
	objectName = "",
	socialGroup = "",
	pvpFaction = "",
	faction = "",
	level = 1,
	chanceHit = 19.75,
	damageMin = 1,
	damageMax = 1,
	baseXp = 0,
	baseHAM = 1,
	baseHAMmax = 1,
	armor = 3,
	resists = {95,85,80,30,10,10,30,45,-1},
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
	optionsBitmask = 0,
	diet = NONE,

	templates = {"object/mobile/dressed_stormtrooper_black_black.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(darknovatrooper, "darknovatrooper")
