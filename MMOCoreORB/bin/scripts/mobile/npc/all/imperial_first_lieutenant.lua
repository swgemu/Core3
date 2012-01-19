imperial_first_lieutenant = Creature:new {
	objectName = "@mob/creature_names:imperial_first_lieutenant",
	socialGroup = "Imperial",
	pvpFaction = "Imperial",
	faction = "",
	level = 20,
	chanceHit = 0.33,
	damageMin = 190,
	damageMax = 200,
	baseXp = 1803,
	baseHAM = 5000,
	baseHAMmax = 6100,
	armor = 0,
	resists = {10,10,10,0,0,0,0,-1,-1},
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
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_imperial_lieutenant_m.iff","object/mobile/dressed_imperial_officer_m_3.iff"},
	lootgroups = {},
	weapons = {"imperial_weapons_medium"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(imperial_first_lieutenant, "imperial_first_lieutenant")