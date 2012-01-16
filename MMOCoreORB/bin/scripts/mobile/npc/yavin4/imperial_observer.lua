imperial_observer = Creature:new {
	objectName = "@mob/creature_names:Imperial observer",
	socialGroup = "self",
	pvpFaction = "self",
	faction = "",
	level = 53,
	chanceHit = 0.54,
	damageMin = 415,
	damageMax = 540,
	baseXp = 5190,
	baseHAM = 11000,
	baseHAMmax = 13000,
	armor = 1,
	resists = {5,5,5,5,5,5,5,5,-1},
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

	templates = {},
	lootgroups = {},
	weapons = {"imperial_weapons_heavy"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(imperial_observer, "imperial_observer")