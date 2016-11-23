sathme_forr = Creature:new {
	objectName = "",
	customName = "Sathme Forr (an artist)",
	socialGroup = "commoner",
	faction = "",
	level = 10,
	chanceHit = 1,
	damageMin = 1,
	damageMax = 1,
	baseXp = 1000,
	baseHAM = 1000,
	baseHAMmax = 1000,
	armor = 0,
	resists = {60,60,60,60,60,60,60,60,-1},
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

	templates = 
	  {"object/mobile/dressed_bestine_rumor12.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "trialsPadawanArtist01ConvoTemplate",
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(sathme_forr, "sathme_forr")