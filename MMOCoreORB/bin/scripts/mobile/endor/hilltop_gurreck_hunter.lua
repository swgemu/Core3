hilltop_gurreck_hunter = Creature:new {
	objectName = "@mob/creature_names:hilltop_gurreck_hunter",
	socialGroup = "gurreck",
	pvpFaction = "",
	faction = "",
	level = 41,
	chanceHit = 0.42,
	damageMin = 340,
	damageMax = 390,
	baseXp = 4006,
	baseHAM = 8600,
	baseHAMmax = 10600,
	armor = 0,
	resists = {50,65,25,25,25,25,25,25,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_wooly",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/gurreck.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(hilltop_gurreck_hunter, "hilltop_gurreck_hunter")