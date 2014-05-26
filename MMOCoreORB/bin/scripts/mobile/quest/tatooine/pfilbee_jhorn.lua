pfilbee_jhorn = Creature:new {
	objectName = "",
	customName = "Pfilbee Jhorn",
	socialGroup = "imperial",
	pvpFaction = "imperial",
	faction = "imperial",
	level = 10,
	chanceHit = 0.28,
	damageMin = 90,
	damageMax = 110,
	baseXp = 356,
	baseHAM = 810,
	baseHAMmax = 990,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
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

	templates = {"object/mobile/dressed_tatooine_pfilbee_jhorn.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "pfilbee_jhorn_mission_giver_convotemplate",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(pfilbee_jhorn, "pfilbee_jhorn")
