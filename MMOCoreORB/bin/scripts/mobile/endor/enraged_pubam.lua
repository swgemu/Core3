enraged_pubam = Creature:new {
	objectName = "@mob/creature_names:enraged_pubam",
	socialGroup = "Pubam",
	pvpFaction = "Pubam",
	faction = "",
	level = 10,
	chanceHit = 0.28,
	damageMin = 130,
	damageMax = 140,
	baseXp = 430,
	baseHAM = 675,
	baseHAMmax = 825,
	armor = 0,
	resists = {-1,-1,-1,10,10,10,10,-1,-1},
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

	templates = {"object/mobile/dulok_male.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(enraged_pubam, "enraged_pubam")