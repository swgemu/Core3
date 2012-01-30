neo_cobral_hitman = Creature:new {
	objectName = "@mob/creature_names:cobral_hitman",
	socialGroup = "Cobral",
	pvpFaction = "Cobral",
	faction = "",
	level = 21,
	chanceHit = 0.34,
	damageMin = 220,
	damageMax = 230,
	baseXp = 1803,
	baseHAM = 5400,
	baseHAMmax = 6600,
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
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {},
	lootGroups = {},
	weapons = {"ranged_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(neo_cobral_hitman, "neo_cobral_hitman")