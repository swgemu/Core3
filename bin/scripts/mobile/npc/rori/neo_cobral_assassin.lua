neo_cobral_assassin = Creature:new {
	objectName = "Neo-Cobral assassin",
	socialGroup = "Cobral",
	pvpFaction = "Cobral",
	faction = "",
	level = 25,
	chanceHit = 0.360000,
	damageMin = 300,
	damageMax = 310,
	baseXp = 2637,
	baseHAM = 5900,
	baseHAMmax = 7200,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"pirate_weapons_medium"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(neo_cobral_assassin, "neo_cobral_assassin")