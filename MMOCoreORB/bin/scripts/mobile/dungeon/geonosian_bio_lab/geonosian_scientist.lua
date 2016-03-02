geonosian_scientist = Creature:new {
	objectName = "@mob/creature_names:geonosian_scientist",
	socialGroup = "geonosian",
	faction = "",
	level = 48,
	chanceHit = 0.49,
	damageMin = 385,
	damageMax = 480,
	baseXp = 4643,
	baseHAM = 10000,
	baseHAMmax = 12200,
	armor = 1,
	resists = {15,15,-1,65,0,30,-1,0,-1},
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
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_geonosian_scientist_01.iff",
		"object/mobile/dressed_geonosian_scientist_02.iff"},
	lootGroups = {
		{
			groups = {
				{group = "geonosian_common", chance = 5000000},
				{group = "geonosian_relic", chance = 5000000}
			}
		}
	},
	weapons = {"geonosian_weapons"},
	conversationTemplate = "",
	attacks = merge(brawlermaster,marksmanmaster,pistoleermaster,riflemanmaster)
}

CreatureTemplates:addCreatureTemplate(geonosian_scientist, "geonosian_scientist")
