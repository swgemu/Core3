imperial_officer_warren = Creature:new {
	objectName = "@mob/creature_names:warren_imperial_officer",
	socialGroup = "warren_imperial",
	pvpFaction = "warren_imperial",
	faction = "warren_imperial",
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

	templates = {
		"object/mobile/warren_imperial_officer_s01.iff",
		"object/mobile/warren_imperial_officer_s02.iff",
		"object/mobile/warren_imperial_officer_s03.iff"},
	lootGroups = {},
	weapons = {"imperial_weapons_medium"},
	conversationTemplate = "",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(imperial_officer_warren, "imperial_officer_warren")
