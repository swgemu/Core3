neo_cobral_boss = Creature:new {
	objectName = "@mob/creature_names:cobral_boss",
	socialGroup = "Cobral",
	pvpFaction = "Cobral",
	faction = "",
	level = 30,
	chanceHit = 0.38,
	damageMin = 280,
	damageMax = 290,
	baseXp = 3097,
	baseHAM = 8300,
	baseHAMmax = 10100,
	armor = 0,
	resists = {0,0,0,40,40,40,40,-1,-1},
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

	templates = {},
	lootGroups = {},
	weapons = {"pirate_weapons_medium"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(neo_cobral_boss, "neo_cobral_boss")