ig_assassin_droid = Creature:new {
	objectName = "",
	socialGroup = "",
	pvpFaction = "",
	faction = "",
	level = 0,
	chanceHit = 0,
	damageMin = 0,
	damageMax = 0,
	baseXp = 0,
	baseHAM = 0,
	baseHAMmax = 0,
	armor = 0,
	resists = {25,25,5,5,5,5,5,-1,-1},
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
	creatureBitmask = KILLER,
	optionsBitmask = 0,
	diet = NONE,

	templates = {},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(ig_assassin_droid, "ig_assassin_droid")