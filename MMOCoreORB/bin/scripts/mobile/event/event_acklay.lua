event_acklay = Creature:new {
	objectName = "@mob/creature_names:geonosian_acklay_bunker_boss",
	customName = "an acklay (event)",
	socialGroup = "geonosian_creature",
	pvpFaction = "geonosian_creature",
	faction = "",
	level = 157,
	chanceHit = 92.5,
	damageMin = 935,
	damageMax = 1580,
	baseXp = 0,
	baseHAM = 96000,
	baseHAMmax = 118000,
	armor = 2,
	resists = {40,45,55,55,45,45,40,40,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 25,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/acklay_hue.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"creatureareacombo",""},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(event_acklay, "event_acklay")
