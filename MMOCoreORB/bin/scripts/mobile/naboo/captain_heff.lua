captain_heff = Creature:new {
	objectName = "@theme_park/warren/warren_system_messages:name_heff",
	socialGroup = "imperial",
	pvpFaction = "imperial",
	faction = "imperial",
	level = 23,
	chanceHit = 1,
	damageMin = 123,
	damageMax = 254,
	baseXp = 2300,
	baseHAM = 3400,
	baseHAMmax = 4300,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
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
	optionsBitmask = 136,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_imperial_captain_m.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "CaptainHeffConversationTemplate",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(captain_heff, "captain_heff")
