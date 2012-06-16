stormtrooper_warren = Creature:new {
	objectName = "@mob/creature_names:warren_stormtrooper",
	socialGroup = "warren_imperial",
	pvpFaction = "warren_imperial",
	faction = "warren_imperial",
	level = 26,
	chanceHit = 0.360000,
	damageMin = 240,
	damageMax = 250,
	baseXp = 2730,
	baseHAM = 7200,
	baseHAMmax = 8800,
	armor = 0,
	resists = {20,20,40,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE + AGGRESSIVE,
	creatureBitmask = PACK + KILLER,
	diet = HERBIVORE,

	aiTemplate = "default",

	templates = {"object/mobile/warren_stormtrooper.iff"},
	lootGroups = {},
	weapons = {"stormtrooper_weapons"},
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(stormtrooper_warren, "stormtrooper_warren")
