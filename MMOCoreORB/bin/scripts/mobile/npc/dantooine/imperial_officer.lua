imperial_officer = Creature:new {
	objectName = "@mob/creature_names:warren_imperial_officer",
	socialGroup = "Warren imp.",
	pvpFaction = "Warren imp.",
	faction = "",
	level = 27,
	chanceHit = 0.37,
	damageMin = 260,
	damageMax = 270,
	baseXp = 2730,
	baseHAM = 8100,
	baseHAMmax = 9900,
	armor = 0,
	resists = {25,25,0,-1,-1,-1,-1,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"imperial_weapons_medium"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(imperial_officer, "imperial_officer")