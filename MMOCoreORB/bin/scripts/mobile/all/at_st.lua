at_st = Creature:new {
	objectName = "@mob/creature_names:at_st",
	socialGroup = "Imperial",
	pvpFaction = "",
	faction = "",
	level = 125,
	chanceHit = 1.27,
	damageMin = 770,
	damageMax = 1250,
	baseXp = 11859,
	baseHAM = 0,
	baseHAMmax = 0,
	armor = 2,
	resists = {35,35,-1,100,100,15,15,100,-1},
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
	optionsBitmask = 0,
	diet = NONE,

	templates = {"object/mobile/atst.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(at_st, "at_st")