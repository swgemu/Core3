frenzied_pubam = Creature:new {
	objectName = "@mob/creature_names:frenzied_pubam",
	socialGroup = "pubam",
	pvpFaction = "pubam",
	faction = "pubam",
	level = 40,
	chanceHit = 0.44,
	damageMin = 385,
	damageMax = 480,
	baseXp = 4006,
	baseHAM = 8800,
	baseHAMmax = 10800,
	armor = 1,
	resists = {0,0,40,40,40,-1,-1,100,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	aiTemplate = "default",

	templates = {
			"object/mobile/dulok_male.iff",
			"object/mobile/dulok_female.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(frenzied_pubam, "frenzied_pubam")